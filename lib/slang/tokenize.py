#!/usr/bin/env python

from clang import cindex
from fnmatch import fnmatch
from itertools import *
from . import customization
import collections
import sys
import weakref

# Twice the number if next/prev calls that can be used to find nearby tokens.
BUFFER_SIZE = 1001

__all__ = [
    'cursorize', 'dumpSource', 'dumpTokens', 'filterCursorsByFilename'
  , 'tokenize'
  , 'FUNCTIONS_KINDS'
  ]

FUNCTION_KINDS = {
    cindex.CursorKind.FUNCTION_TEMPLATE
  , cindex.CursorKind.FUNCTION_DECL
  , cindex.CursorKind.CXX_METHOD
  , cindex.CursorKind.CONSTRUCTOR
  , cindex.CursorKind.DESTRUCTOR
  , cindex.CursorKind.CONVERSION_FUNCTION
  }
def mrca(a, b):
  '''Most-recent common (semantic) ancestor for cursors.'''
  if a is None or b is None: return None
  s = set()
  for i,j in izip(semanticAncestors(a), semanticAncestors(b)):
    if i in s: return i
    s.add(i)
    if j in s: return j
    s.add(j)
  assert a._tu.cursor == b._tu.cursor
  return a._tu.cursor

cindex.TokenKind.register(100, 'WHITESPACE')

class Eof(Exception): pass

class WhitespaceToken(object):
  def __init__(self, prev_tok, next_tok, source):
    assert _filenameFromCursor(prev_tok.cursor) == source.name
    if next_tok is not None:
      assert prev_tok._tu.cursor == next_tok._tu.cursor
      assert _filenameFromCursor(next_tok.cursor) == source.name
    offset = source.tell()
    self.spelling = source.read(1)
    if self.spelling == '': raise Eof()
    self.kind = cindex.TokenKind.WHITESPACE
    if next_tok is None:
      self.cursor = list(semanticAncestors(prev_tok.cursor))[-1]
    else:
      self.cursor = mrca(prev_tok.cursor, next_tok.cursor)

    begin,end = (
        cindex.SourceLocation.from_offset(
            prev_tok._tu
          , prev_tok.location.file
          , offset + i
          )
        for i in range(2)
      )
    self.location = begin
    self.extent = cindex.SourceRange.from_locations(begin, end)
    if not WhitespaceToken.isWhitespace(self.spelling):
      raise ValueError('whitespace expected at %s, got "%s"'
          % (self.location, self.spelling)
        )
  @staticmethod
  def isWhitespace(ch):
    return ch.isspace() or ch == '\\' or ch == ''
  @property
  def isLineEnding(self):
    return self.spelling == '\n' or self.spelling == '\\'
  @property
  def isSpace(self):
    return self.spelling == ' ' or self.spelling == '\t'
  @property
  def isNil(self):
    return self.spelling == ''
  @property
  def key(self):
    return self.location.key
  __repr__ = cindex.Token.__repr__.__func__

def cursorize(cursor):
  yield cursor
  for child in cursor.get_children():
    for c in cursorize(child):
      yield c

def filterCursorsByFilename(cursors, predicate):
  def ifilter_predicate(cursor):
    file = cursor.location.file
    ans = file is None or predicate(file.name)
    return ans
  return ifilter(ifilter_predicate, cursors)

def _getTokens(cursor, source, **kwds):
  '''
  Monkey-patches cindex.get_tokens to work around inconsistencies.

  The last token for functions requires special handling.  Consider:

      (1) bool foo();
      (2) bool foo() {} // anything

  In the declaration (case 1), the semicolon, which belongs to the cursor of
  the surrounding context, is included in the cursor's tokens.  In the
  definition (case 2), the token following the function definition, which
  could be anything, is included.
  '''
  tokens = sorted(cursor.get_tokens())
  if cursor.kind in FUNCTION_KINDS and tokens and tokens[-1].spelling != ';':
    return tokens[:-1]
  else:
    return tokens

def _getWsBetween(prev_tok, next_tok, source, **kwds):
  buffer = []
  source.seek(prev_tok.extent.end.offset)
  end = 2**63 if next_tok is None else next_tok.extent.start.offset
  while source.tell() < end:
    try:
      ws = WhitespaceToken(prev_tok, next_tok, source)
    except Eof:
      break;
    assert not ws.isNil
    if ws.isLineEnding and kwds.get('strip_trailing_whitespace'):
      if ws.spelling == '\\':
        for item in buffer: yield item
      buffer = []
      yield ws
    else:
      buffer.append(ws)
  for ws in buffer:
    yield ws

def _filenameFromCursor(cursor):
  if cursor.location.file:
    return cursor.location.file.name
  else:
    return cursor._tu.spelling

class MyNone(object): pass

class WeakRef(weakref.ref):
  def __call__(self):
    obj = weakref.ref.__call__(self)
    if obj is None:
      raise RuntimeError('token buffer too small')
    elif obj is MyNone:
      return None
    else:
      return obj

def linked(inner):
  '''Adds prev/next members to a stream of tokens to navigate more easily.'''
  def f(*args, **kwds):
    gen = inner(*args, **kwds)
    xprev = MyNone
    for x in gen:
      x.prev = WeakRef(xprev)
      if xprev is not MyNone:
        xprev.next = WeakRef(x)
        yield xprev
      xprev = x
    if xprev is not None:
      xprev.next = WeakRef(MyNone)
      yield xprev
  return f

def buffered(inner):
  '''Keeps enough tokens around for prev/next to work in a current region.'''
  def f(*args, **kwds):
    gen = inner(*args, **kwds)
    buf = collections.deque(maxlen=BUFFER_SIZE)
    for i in xrange(BUFFER_SIZE):
      try:
        buf.append(gen.next())
      except StopIteration:
        for x in buf: yield x
        return
    middle = BUFFER_SIZE // 2
    for i in xrange(middle): yield buf[i]
    for x in gen:
      yield buf[middle]
      buf.append(x)
    for i in xrange(middle, len(buf)): yield buf[i]
  return f

@buffered
@linked
def tokenize(cursor, **kwds):
  '''
  Produces the complete sequence of tokens associated with the given cursor.
  Inserts whitespace tokens.
  '''
  # source = open(cursor._tu.spelling, 'r')
  filename = _filenameFromCursor(cursor)
  source = open(filename, 'r')
  prev_tok = None
  raw_tokens = _getTokens(cursor, source, **kwds)
  if not raw_tokens: return
  if kwds.pop('include_predent', None):
    parent = cursor
    while parent and parent.extent == cursor.extent:
      parent = cursor.lexical_parent
    if parent:
      assert _filenameFromCursor(parent) == filename
      more_tokens = sorted(parent.get_tokens())
      try:
        ibegin = more_tokens.index(raw_tokens[0])
      except ValueError:
        pass
      else:
        assert ibegin > 0
        prev_tok = more_tokens[ibegin-1]
  for next_tok in raw_tokens:
    if prev_tok:
      for ws in _getWsBetween(prev_tok, next_tok, source):
        yield ws
    yield next_tok
    prev_tok = next_tok

def _updateContext(context, prev_cursor, next_cursor):
  '''Helper for dumpTokens.'''
  def show(close):
    cursor = context[-1]
    print '%s[%s%s: %s]' % (
        '  ' * (len(context) - 1)
      , '/' if close else ''
      , cursor
      , hex(hash(cursor))
      )
  if prev_cursor is not None:
    ancestor = mrca(prev_cursor, next_cursor)
    try:
      pos = context.index(ancestor)
    except:
      pos = -1
    for i in xrange(pos+1, len(context)):
      show(True)
      context.pop()
  stop = None if not context else context[-1]
  def showPostorder(cursor):
    if cursor is None: return
    if stop is None or cursor != stop:
      showPostorder(cursor.semantic_parent)
    else: return
    context.append(cursor)
    show(False)
  showPostorder(next_cursor)

def dumpTokens(cursor):
  prev_cursor = None
  context = []
  for tok in tokenize(cursor):
    # Print the cursors as they change.
    _updateContext(context, prev_cursor, tok.cursor)
    prev_cursor = tok.cursor

    # Print the tokens.
    repr_ = repr(tok.spelling) if tok.spelling == ' ' else \
        repr(tok.spelling).strip("'")
    print '%s    %-15s %s' % ('  ' * len(context), tok.kind.name.lower(), repr_)
  _updateContext(context, prev_cursor, None)

def semanticAncestors(cursor):
  while cursor is not None:
    yield cursor
    cursor = cursor.semantic_parent

def dumpSource(cursor, stream=sys.stdout, **kwds):
  for tok in tokenize(cursor, **kwds):
    stream.write(tok.spelling)

if __name__ == '__main__':
  """Usage: call with <filename>"""
  index = cindex.Index.create()
  filename = sys.argv[1]
  if filename.endswith('.ast'):
    tu = index.read(filename)
  else:
    tu = index.parse(filename)
  # dumpTokens(tu.cursor)
  dumpSource(tu.cursor)


#!/usr/bin/env python2

from clang import cindex
from fnmatch import fnmatch
from itertools import ifilter, dropwhile, takewhile
import sys

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
# Order and hash tokens and cursors by their location in the source file.
cindex.SourceLocation.__lt__ = lambda lhs,rhs: lhs.offset < rhs.offset
cindex.SourceLocation.__gt__ = lambda lhs,rhs: lhs.offset > rhs.offset
cindex.SourceLocation.__le__ = lambda lhs,rhs: lhs.offset <= rhs.offset
cindex.SourceLocation.__ge__ = lambda lhs,rhs: lhs.offset >= rhs.offset
cindex.SourceLocation.key = property(lambda self: (self.file.name, self.offset))
cindex.Token.__eq__ = lambda lhs,rhs: lhs.location.__eq__(rhs.location)
cindex.Token.__ne__ = lambda lhs,rhs: lhs.location.__ne__(rhs.location)
cindex.Token.__lt__ = lambda lhs,rhs: lhs.location.__lt__(rhs.location)
cindex.Token.__gt__ = lambda lhs,rhs: lhs.location.__gt__(rhs.location)
cindex.Token.__le__ = lambda lhs,rhs: lhs.location.__le__(rhs.location)
cindex.Token.__ge__ = lambda lhs,rhs: lhs.location.__ge__(rhs.location)
cindex.Token.key = property(lambda self: self.location.key)
cindex.Token.__hash__ = lambda self: hash(self.key)
cindex.Cursor.__lt__ = lambda lhs,rhs: lhs.location.__lt__(rhs.location)
cindex.Cursor.__gt__ = lambda lhs,rhs: lhs.location.__gt__(rhs.location)
cindex.Cursor.__le__ = lambda lhs,rhs: lhs.location.__le__(rhs.location)
cindex.Cursor.__ge__ = lambda lhs,rhs: lhs.location.__ge__(rhs.location)
def Cursor_key(self):
  if self.location.file is not None:
    return self.location.key
  assert self.kind == cindex.CursorKind.TRANSLATION_UNIT
  return self.spelling
cindex.Cursor.key = property(Cursor_key)
cindex.Cursor.__hash__ = lambda self: hash(self.key)

Token__getattribute__old = cindex.Token.__getattribute__
def Token__getattribute__new(self, name):
  # Attributes requiring post-processing.
  attr = Token__getattribute__old(self, name)
  if name == 'cursor' and attr.kind == cindex.CursorKind.INVALID_FILE:
    return attr._tu.cursor
  return attr
cindex.Token.__getattribute__ = Token__getattribute__new

def _generic_repr(obj):
  return '<%s: kind=%s, spelling=%s>' % (
      type(obj).__name__, obj.kind.name, repr(obj.spelling)
    )
cindex.Cursor.__repr__ = _generic_repr
cindex.Token.__repr__ = _generic_repr

def mrca(a, b):
  '''Most-recent common (semantic) ancestor for cursors.'''
  if a is None or b is None: return None
  ancestors = {ancestor for ancestor in semanticAncestors(a)}
  for x in semanticAncestors(b):
    if x in ancestors:
      return x
  # Means bugginess in cindex.
  assert a._tu.cursor == b._tu.cursor
  return a._tu.cursor

cindex.TokenKind.register(100, 'WHITESPACE')

class Eof(Exception): pass

class WhitespaceToken(object):
  def __init__(self, prior_token, next_token, source):
    assert prior_token._tu.cursor == next_token._tu.cursor
    offset = source.tell()
    self.spelling = source.read(1)
    if self.spelling == '': raise Eof()
    self.kind = cindex.TokenKind.WHITESPACE
    self.cursor = mrca(prior_token.cursor, next_token.cursor)
    begin,end = (
        cindex.SourceLocation.from_offset(
            prior_token._tu
          , prior_token.location.file
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
  def isNil(self):
    return self.spelling == ''
  __repr__ = _generic_repr

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

def _getTokens(cursor):
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
  # while source.tell() < next_tok.location.offset:
  while source.tell() < next_tok.extent.start.offset:
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

def tokenize(cursor, **kwds):
  '''
  Produces the complete sequence of tokens associated with the given cursor.
  Inserts whitespace tokens.
  '''
  source = open(cursor._tu.spelling, 'r')
  prev_tok = None
  for next_tok in _getTokens(cursor):
    if prev_tok:
      for ws in _getWsBetween(prev_tok, next_tok, source):
        yield ws
      # source.seek(prev_tok.extent.end.offset)
      # buffer = []
      # while source.tell() < next_tok.location.offset:
      #   ws = WhitespaceToken(prev_tok, next_tok, source)
      #   assert not ws.isNil
      #   if ws.isLineEnding and strip_trailing_whitespace:
      #     if ws.spelling == '\\':
      #       for item in buffer: yield item
      #     buffer = []
      #     yield ws
      #   else:
      #     buffer.append(ws)
      # for ws in buffer: yield ws
    yield next_tok
    prev_tok = next_tok
  if prev_tok:
      for ws in _getWsBetween(prev_tok, next_tok, source):
        yield ws
    # source.seek(prev_tok.extent.end.offset)
    # buffer = []
    # while(True):
    #   try:
    #     ws = WhitespaceToken(prev_tok, next_tok, source)
    #     assert not ws.isNil
    #     if ws.isLineEnding and kwds.get('strip_trailing_whitespace'):
    #       if ws.spelling == '\\':
    #         for item in buffer: yield item
    #       buffer = []
    #       yield ws
    #     else:
    #       buffer.append(ws)
    #   except:
    #     break
    # for ws in buffer:
    #   yield ws

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

def indexOf(cursor):
  siblings = list(cursor.lexical_parent.get_children())
  assert sum(1 if s == cursor else 0 for s in siblings) == 1
  return siblings.index(cursor)

def siblings(cursor):
  siblings = cursor.lexical_parent.get_children()
  return (sib for sib in siblings if sib != cursor)

def prior_siblings(cursor):
  return takewhile(
      lambda s: s != cursor
    , cursor.lexical_parent.get_children()
    )

def subsequent_siblings(cursor):
  return dropwhile(
      lambda s: s != cursor
    , cursor.lexical_parent.get_children()
    )
     
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
  dumpTokens(tu.cursor)
  # dumpSource(tu.cursor)


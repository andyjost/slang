#!/usr/bin/env python2
import sys
from clang import cindex
import code
import pdb

__all__ = ['tokenize']

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

def semanticAncestors(cursor):
  while cursor is not None:
    yield cursor
    cursor = cursor.semantic_parent

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

class WhitespaceToken(object):
  def __init__(self, prior_token, next_token, source):
    assert prior_token._tu.cursor == next_token._tu.cursor
    offset = source.tell()
    self.spelling = source.read(1)
    if not self.spelling.isspace() and self.spelling != '\\':
      raise Exception('whitespace expected')
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

  @property
  def isLineEnding(self):
    return self.spelling == '\n' or self.spelling == '\\'

  __repr__ = _generic_repr

def tokenize(cursor, strip_trailing_whitespace=True):
  '''
  Produces the complete sequence of tokens associated with the given cursor.
  Inserts whitespace tokens.
  '''
  source = open(cursor._tu.spelling, 'r')
  prev_tok = None
  for next_tok in sorted(cursor.get_tokens()):
    if prev_tok:
      source.seek(prev_tok.extent.end.offset)
      buffer = []
      while source.tell() < next_tok.location.offset:
        ws = WhitespaceToken(prev_tok, next_tok, source)
        if ws.isLineEnding and strip_trailing_whitespace:
          if ws.spelling == '\\':
            for item in buffer: yield item
          buffer = []
          yield ws
        else:
          buffer.append(ws)
      for ws in buffer: yield ws
    yield next_tok
    prev_tok = next_tok
  if prev_tok:
    source.seek(prev_tok.extent.end.offset)
    buffer = []
    while(True):
      try:
        ws = WhitespaceToken(prev_tok, next_tok, source)
        if ws.isLineEnding and strip_trailing_whitespace:
          if ws.spelling == '\\':
            for item in buffer: yield item
          buffer = []
          yield ws
        else:
          buffer.append(ws)
      except:
        break
    for ws in buffer:
      yield ws

# def graphize(cursor):

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

def generateSource(cursor):
  for tok in tokenize(cursor):
    sys.stdout.write(tok.spelling)

if __name__ == '__main__':
  """Usage: call with <filename>"""
  index = cindex.Index.create()
  filename = sys.argv[1]
  if filename.endswith('.ast'):
    tu = index.read(filename)
  else:
    tu = index.parse(filename)

  # generateSource(tu.cursor)
  dumpTokens(tu.cursor)
  # tokens = list(tokenize(tu.cursor))


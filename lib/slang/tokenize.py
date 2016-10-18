#!/usr/bin/env python2
import sys
from clang import cindex

__all__ = ['tokenize']

# Order tokens by their location in the source file.
cindex.SourceLocation.__lt__ = lambda lhs,rhs: lhs.offset < rhs.offset
cindex.SourceLocation.__gt__ = lambda lhs,rhs: lhs.offset > rhs.offset
cindex.SourceLocation.__le__ = lambda lhs,rhs: lhs.offset <= rhs.offset
cindex.SourceLocation.__ge__ = lambda lhs,rhs: lhs.offset >= rhs.offset
cindex.Token.__eq__ = lambda lhs,rhs: lhs.location.__eq__(rhs.location)
cindex.Token.__ne__ = lambda lhs,rhs: lhs.location.__ne__(rhs.location)
cindex.Token.__lt__ = lambda lhs,rhs: lhs.location.__lt__(rhs.location)
cindex.Token.__gt__ = lambda lhs,rhs: lhs.location.__gt__(rhs.location)
cindex.Token.__le__ = lambda lhs,rhs: lhs.location.__le__(rhs.location)
cindex.Token.__ge__ = lambda lhs,rhs: lhs.location.__ge__(rhs.location)

cindex.TokenKind.register(100, 'WHITESPACE')

def _generic_repr(obj):
  return '<%s: kind=%s, spelling=%s>' % (
      type(obj).__name__, obj.kind.name, repr(obj.spelling)
    )

cindex.Cursor.__repr__ = _generic_repr
cindex.Token.__repr__ = _generic_repr

class WhitespaceToken(object):
  def __init__(self, translation_unit, prior_token, source):
    offset = source.tell()
    self.spelling = source.read(1)
    if not self.spelling.isspace() and self.spelling != '\\':
      raise Exception('whitespace expected')
    self.kind = cindex.TokenKind.WHITESPACE
    self.cursor = prior_token.cursor
    begin,end = (
        cindex.SourceLocation.from_offset(
            translation_unit
          , prior_token.location.file
          , offset + i
          )
        for i in range(2)
      )
    self.location = begin
    self.extent = cindex.SourceRange.from_locations(begin, end)

  __repr__ = _generic_repr

def tokenize(cursor, strip_trailing_whiespace=True):
  '''
  Produces the complete sequence of tokens associated with the given cursor.
  Inserts whitespace tokens.
  '''
  assert cursor.kind == cindex.CursorKind.TRANSLATION_UNIT
  source = open(cursor.spelling, 'r')
  prev = None
  for tok in sorted(cursor.get_tokens()):
    if prev:
      source.seek(prev.extent.end.offset)
      while source.tell() < tok.location.offset:
        yield WhitespaceToken(cursor.translation_unit, prev, source)
    yield tok
    prev = tok
  if prev:
    source.seek(prev.extent.end.offset)
    while(True):
      try:
        yield WhitespaceToken(cursor.translation_unit, prev, source)
      except:
        break

def dumpTokens(cursor):
  prev_cursor = None
  for tok in tokenize(cursor):
    # Print the cursors as they change.
    try:
      if prev_cursor != tok.cursor:
        print('[%s]' % tok.cursor.kind.name)
    except: pass
    prev_cursor = cursor

    # Print the tokens.
    repr_ = repr(tok.spelling) if tok.spelling == ' ' else \
        repr(tok.spelling).strip("'")
    print '    %-15s %s' % (tok.kind.name.lower(), repr_)

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
  generateSource(tu.cursor)


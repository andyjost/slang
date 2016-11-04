'''
Customizations to the Clang cindex library.
'''
from clang import cindex

# def firstitem(seq):
#   for s in seq: break
#   try:
#     yield s
#   except NameError:
#     pass
# 
# def lastitem(seq):
#   for s in seq: pass
#   try:
#     yield s
#   except NameError:
#     pass

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
# cindex.Cursor.prev = lambda self: lastitem(features.prior_siblings(self))
# cindex.Cursor.next = lambda self: firstitem(features.subsequent_siblings(self))
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


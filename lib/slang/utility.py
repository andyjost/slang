from clang.cindex import CursorKind, TokenKind
import itertools
import re

FUNCTION_KINDS = {
    CursorKind.FUNCTION_TEMPLATE
  , CursorKind.FUNCTION_DECL
  , CursorKind.CXX_METHOD
  , CursorKind.CONSTRUCTOR
  , CursorKind.DESTRUCTOR
  , CursorKind.CONVERSION_FUNCTION
  }
# METHODS
# TEMPLATES
# SPECIAL_METHODS (ctor/dtor)

def asserted(inner):
  def nested(*args, **kwds):
    asserts = kwds.pop('assert_', [])
    r = inner(*args, **kwds)
    for pred in asserts:
      assert pred(r)
    return r
  return nested

def fwdfrom(item):
  while item:
    yield item
    item = item.next()
  
def revfrom(item):
  while item:
    yield item
    item = item.prev()

def fwduntil(item, sentinal):
  for x in fwdfrom(item):
    if x == sentinal:
      return
    yield x

def revuntil(item, sentinal):
  for x in revfrom(item):
    if x == sentinal:
      return
    yield x

@asserted
def first(seq, **kwds):
  return seq.next()

@asserted
def last(seq, **kwds):
  for x in seq: pass
  return x

def empty(seq):
  try:
    seq.next()
    return False
  except StopIteration:
    return True

def unitize(seq):
  '''Convert a sequence of one into it's only element.'''
  it = seq.next()
  try:
    seq.next()
    raise TypeError('expected a sequence with one element')
  except:
    return it

def select(cursors, preds=[], filename_pattern=None):
  if filename_pattern is not None:
    cursors = filterCursorsByFilename(
        cursors, lambda filename: re.match(filename_pattern, filename)
      )
  for pred in preds:
    cursors = itertools.ifilter(pred, cursors)
  return cursors

def uselect(*args, **kwds):
  return unitize(select(*args, **kwds))


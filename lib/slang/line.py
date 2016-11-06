'''
Implements class Line.
'''

from .utility import *
from itertools import *
from memoized_property import memoized_property as memoprop

def index(cursor):
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

class Range(object):
  '''A range of tokens.'''
  def __init__(self, get_begin, get_end):
    self._get_begin = get_begin
    self._get_end = get_end

  @memoprop
  def begin(self): return self._get_begin()

  @memoprop
  def end(self): return self._get_end()

  def __iter__(self):
    end = self.end
    for obj in fwdfrom(self.begin):
      if obj == end: return
      yield obj

  def __str__(self):
    return ''.join(obj.spelling for obj in self)

  @memoprop
  def len(self): return sum(1 for obj in self)

  def __len__(self): return self.len

  def key(self): return (self.begin, self.end)
  def __eq__(self, arg): return self.key == arg.key
  def __ne__(self, arg): return self.key != arg.key
  def __le__(self, arg): return self.key <= arg.key
  def __ge__(self, arg): return self.key >= arg.key
  def __lt__(self, arg): return self.key < arg.key
  def __gt__(self, arg): return self.key > arg.key


class Line(Range):
  def __init__(self, reftoken):
    def get_begin():
      for token in revfrom(reftoken.prev()):
        if getattr(token, 'isLineEnding', False):
          return token.next()
      return None
    def get_end():
      for token in fwdfrom(reftoken):
        if getattr(token, 'isLineEnding', False):
          return token
      return None
    Range.__init__(self, get_begin, get_end)

  @memoprop
  def indent(self):
    tokens = takewhile(lambda token: getattr(token, 'isSpace', False), self)
    return sum(1 for token in tokens)

  @memoprop
  def columns(self): return len(str(self))

  def prev(self): return Line(self.begin.prev())
  def next(self): return Line(self.end.next())


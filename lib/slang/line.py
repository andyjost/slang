'''
Implements class Line.
'''

from . import customization
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

def fwdfrom(item):
  while item:
    yield item
    item = item.next()

def revfrom(item):
  while item:
    yield item
    item = item.prev()

class Line(object):
  def __init__(self, token):
    self._token = token

  def __iter__(self):
    end = self.end
    for token in fwdfrom(self.begin):
      if token == end: return
      yield token

  @memoprop
  def begin(self):
    '''Returns the first token of the line (i.e., after the newline).'''
    for token in revfrom(self._token.prev()):
      if getattr(token, 'isLineEnding', False):
        return token.next()
    return None

  @memoprop
  def end(self):
    '''Returns the last token of the line (i.e., the newline).'''
    for token in fwdfrom(self._token):
      if getattr(token, 'isLineEnding', False):
        return token
    return None

  @memoprop
  def indent(self):
    tokens = takewhile(lambda token: getattr(token, 'isSpace', False), self)
    return sum(1 for token in tokens)

  def __str__(self):
    return ''.join(token.spelling for token in self)

  @memoprop
  def columns(self): return len(str(self))

  @memoprop
  def len(self): return sum(1 for token in self)

  def __len__(self): return self.len

  def prev(self): return Line(self.begin.prev())
  def next(self): return Line(self.end.next())

  def key(self): return (self.begin, self.end)
  def __eq__(self, arg): return self.key == arg.key
  def __ne__(self, arg): return self.key != arg.key
  def __le__(self, arg): return self.key <= arg.key
  def __ge__(self, arg): return self.key >= arg.key
  def __lt__(self, arg): return self.key < arg.key
  def __gt__(self, arg): return self.key > arg.key


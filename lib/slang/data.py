from __future__ import division
from clang import cindex
from clang.cindex import TokenKind, CursorKind
from .utility import *
from .tokenize import *
from . import line
from fnmatch import fnmatch
import os
import re
import sys
import warnings
from itertools import *
from memoized_property import memoized_property as memoprop
import operator
import functools
import math

# These can be quite large.
CACHE_AST_FILES = False

# Set up include directories.
#    '-nostdinc', '-nostdinc++'
DEFAULT_ARGS = ['-std=c++11', '-I/usr/lib/llvm-3.8/lib/clang/3.8.0/include']

def parseDirectory(dirname, glob='*.[ch]pp', args=[]):
  for dirpath,_,filenames in os.walk(dirname):
    for filename in filenames:
      abspath = os.path.join(dirpath, filename)
      if not fnmatch(abspath, glob):
        continue
      tu = parseFile(abspath, args)
      if tu is not None:
        yield tu

def parseFile(filename, args=[]):
  index = cindex.Index.create()
  astpath = filename + '.ast'
  if os.path.isfile(astpath):
    return index.read(astpath)
  else:
    try:
      tu = index.parse(filename, args=args+DEFAULT_ARGS)
    except:
      warnings.warn('Failed to parse %s' % filename)
      raise
    if CACHE_AST_FILES:
      tu.save(astpath)
    if len(tu.diagnostics):
      msg = "%d diagnostic message(s) when parsing %s" \
          % (len(tu.diagnostics), filename)
      warnings.warn(msg)
      for msg in tu.diagnostics:
        print >>sys.stderr, msg
    return tu

def filterCursorsByFilename(cursors, predicate):
  def ifilter_predicate(cursor):
    file = cursor.location.file
    ans = file is None or predicate(file.name)
    return ans
  return ifilter(ifilter_predicate, cursors)

def select(cursors, preds=[], filename_pattern=None):
  if filename_pattern is not None:
    cursors = filterCursorsByFilename(
        cursors, lambda filename: re.match(filename_pattern, filename)
      )
  for pred in preds:
    cursors = ifilter(pred, cursors)
  return cursors

def _wrap_unary(op):
  @functools.wraps(op)
  def wrapper(arg):
    if callable(arg):
      return lambda x: op(arg(x))
    else:
      return op(arg)
  return wrapper
# def _wrap_unary(op):
#   @functools.wraps(op)
#   def wrapper(arg):
#     assert callable(arg)
#     return lambda x: op(arg(x))
#   return wrapper
#   @functools.wraps(op)
#   def wrapper(*args):
#     assert len(args) < 2
#     try:
#       (f,) = args
#     except ValueError:
#       return lambda x: op(x)
#     else:
#       return lambda x: op(f(x))
#   return wrapper
#
# # not_(): \x -> not x
# # not_(is_function): \x -> not is_function(x)
not_ = _wrap_unary(operator.not_)
is_ = _wrap_unary(operator.is_)

def _wrap_binary(op):
  @functools.wraps(op)
  def wrapper(*args):
    assert len(args) in [1,2]
    try:
      lhs,rhs = args
    except ValueError:
      (rhs,) = args
      if callable(rhs):
        return lambda x: op(x,rhs(x))
      else:
        return lambda x: op(x,rhs)
    else:
      if callable(lhs):
        if callable(rhs):
          return lambda x: op(lhs(x),rhs(x))
        else:
          return lambda x: op(lhs(x),rhs)
      else:
        if callable(rhs):
          return lambda x: op(lhs,rhs(x))
        else:
          return lambda x: op(lhs,rhs)
  return wrapper

# lt(line_length, 80): \x -> line_length(x) < 80
lt = _wrap_binary(operator.lt)
gt = _wrap_binary(operator.gt)
ge = _wrap_binary(operator.ge)
le = _wrap_binary(operator.le)
eq = _wrap_binary(operator.eq)
ne = _wrap_binary(operator.ne)
and_ = _wrap_binary(operator.and_)
or_ = _wrap_binary(operator.or_)

def uselect(*args, **kwds):
  return unitize(select(*args, **kwds))

@_wrap_unary
def is_function(cursor):
  return cursor.kind in FUNCTION_KINDS

@_wrap_unary
def function_body(cursor):
  assert is_function(cursor)
  return uselect(cursorize(cursor), [is_compound_stmt])

@_wrap_unary
def is_definition(cursor):
  if not is_function(cursor): return False
  children = list(cursor.get_children())
  result = children and is_compound_stmt(children[-1])
  assert result == cursor.is_definition()
  return result

@_wrap_unary
def function_has_empty_body(cursor):
  body = function_body(cursor)
  return empty(select(cursorize(body), [ne(body)]))

@_wrap_unary
def function_body_stmts(cursor):
  body = function_body(cursor)
  return sum(1 for _ in body.children)

@_wrap_unary
def is_compound_stmt(cursor):
  return cursor.kind == cindex.CursorKind.COMPOUND_STMT

@_wrap_unary
def owned_by(cursor):
  return lambda obj: cursor == Cursor(obj)

@_wrap_binary
def is_kind(cursor, kind):
  return cursor.kind == kind

@_wrap_unary
def is_class_like(cursor):
  return cursor.kind in (
      CursorKind.CLASS_DECL
    , CursorKind.CLASS_TEMPLATE
    , CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION
    )

@_wrap_unary
def is_constructor(cursor):
  if cursor.kind == CursorKind.CONSTRUCTOR:
    return True
  if cursor.kind == CursorKind.FUNCTION_TEMPLATE:
    parent = cursor.semantic_parent
    if parent and is_class_like(parent):
      # E.g., 'optional<T>' -> 'optional'
      basename = lambda s: s.split('<')[0]
      return basename(parent.spelling) == basename(cursor.spelling)
  return False

def is_spelled(spelling):
  return lambda obj: spelling == obj.spelling

@_wrap_binary
def contains_keyword(cursor, spelling):
  found = select(
      cursor.tokens, [is_kind(TokenKind.KEYWORD), is_spelled(spelling)]
    )
  return not empty(found)

@_wrap_unary
def is_whitespace(token):
  try:
    return token.isWhitespace
  except AttributeError:
    return False

@_wrap_unary
def is_space(token):
  try:
    return token.isSpace
  except AttributeError:
    return False

@_wrap_unary
def is_line_end(token):
  try:
    return token.isLineEnding
  except AttributeError:
    return False

@_wrap_unary
def length_as_single_line(cursor):
  counting = True # To skip strings of whitespace.
  length = 0
  for token in cursor.tokens:
    if is_whitespace(token):
      if counting:
        length += 1
        counting = False
    else:
      counting = True
      length += len(token.spelling)
  return length

@_wrap_unary
def function_has_newline_before_body(cursor):
  body = function_body(cursor)
  p = uselect(cursor.tokens, [owned_by(body), is_spelled('{')])
  prev = uselect(revfrom(p.prev()), [or_(not_(is_whitespace), is_line_end)])
  return is_line_end(prev)

def probability(
    seq, what, given=[]
  , on_true=lambda _:None, on_false=lambda _:None
  ):
  total = 0
  positive = 0
  for item in seq:
    if all(condition(item) for condition in given):
      total += 1
      if what(item):
        on_true(item)
        positive += 1
      else:
        on_false(item)
  if total == 0:
    return None
  return positive / total

def entropy(p):
  assert 0 <= p <= 1
  if p == 1: return 0
  q = 1 - p
  return (p*math.log(p) + q*math.log(q)) / -math.log(2)

def entropic_quality(seq, what, given=[], *args, **kwds):
  a = entropy(probability(seq, what, given, *args, **kwds))
  not_given = reduce(lambda a,b: or_(a, not_(b)), given, lambda *args: False)
  b = entropy(probability(seq, what, [not_given], *args, **kwds))
  return (a + b) / 2

class SourceIndex(object):
  def __init__(self, source, args=[]):
    self.source = source
    self.args = args

  @property
  def translation_units(self):
    if os.path.isdir(self.source):
      return parseDirectory(self.source)
    if os.path.isfile(self.source):
      return iter([parseFile(self.source)])
    return []

  def cursors(self, preds=[]):
    for tu in self.translation_units:
      same_file = lambda cursor:                                   \
          cursor.location.file is not None and                     \
          os.path.samefile(cursor.location.file.name, tu.spelling) \
        ##
      cursors = cursorize(tu)
      for cursor in select(cursors, preds=[same_file]+preds):
        yield Cursor(cursor)

class Cursor(object):
  def __init__(self, cursor):
    self.cursor = getattr(cursor,'cursor',cursor)

  def __getattribute__(self, name):
    try:
      cursor = object.__getattribute__(self, 'cursor')
      return getattr(cursor, name)
    except AttributeError:
      return object.__getattribute__(self, name)

  @property
  def lines(self):
    try:
      first = line.Line(self.tokens.next())
    except StopIteration:
      return iter([])
    return fwdfrom(first)

  @property
  def tokens(self):
    extent = self.cursor.extent
    offset_begin = extent.start.offset
    offset_end = extent.end.offset
    return ifilter(
        lambda t: offset_begin <= t.location.offset <= offset_end
      , self._token_window
      )

  @property
  def children(self):
    return imap(Cursor, self.cursor.get_children())

  @memoprop
  def _token_window(self):
    '''Get the window of tokens for this cursor.'''
    dist = BUFFER_SIZE // 2
    return tuple(tokenize(self.cursor, expandby=(dist,dist)))

  # def __str__(self): return str(self.cursor)
  def __str__(self):
    return ''.join([t.spelling for t in self.tokens])
  def __repr__(self): return repr(self.cursor)
  def __eq__(self, other): return self.cursor == Cursor(other).cursor
  def __ne__(self, other): return self.cursor != Cursor(other).cursor
  def __le__(self, other): return self.cursor <= Cursor(other).cursor
  def __ge__(self, other): return self.cursor >= Cursor(other).cursor
  def __lt__(self, other): return self.cursor < Cursor(other).cursor
  def __gt__(self, other): return self.cursor > Cursor(other).cursor

def cursorize(cursor):
  cursor = getattr(cursor, 'cursor', cursor)
  yield Cursor(cursor)
  for child in cursor.get_children():
    for c in cursorize(child):
      yield c


from clang import cindex
from fnmatch import fnmatch
from . import line
from memoized_property import memoized_property as memoprop
from .tokenize import *
from .utility import *
import os
import warnings

# These can be quite large.
CACHE_AST_FILES = False
VERBOSE = False

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
    if VERBOSE and len(tu.diagnostics):
      msg = "%d diagnostic message(s) when parsing %s" \
          % (len(tu.diagnostics), filename)
      warnings.warn(msg)
      for diag in tu.diagnostics:
        print >>sys.stderr, diag.spelling
    return tu

def filterCursorsByFilename(cursors, predicate):
  def ifilter_predicate(cursor):
    file = cursor.location.file
    ans = file is None or predicate(file.name)
    return ans
  return ifilter(ifilter_predicate, cursors)

class SourceIndex(object):
  def __init__(self, inputs, args=[]):
    self.inputs = [inputs] if isinstance(inputs, str) else list(inputs)
    self.args = args

  @property
  def translation_units(self):
    for item in self.inputs:
      if os.path.isdir(item):
        for x in parseDirectory(item):
          yield x
      if os.path.isfile(item):
        yield parseFile(item)

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

  def __str__(self): return str(self.cursor)
  # def __str__(self): return ''.join([t.spelling for t in self.tokens])
  def __repr__(self): return repr(self.cursor)
  def __eq__(self, other): return self.cursor == Cursor(other).cursor
  def __ne__(self, other): return self.cursor != Cursor(other).cursor
  def __le__(self, other): return self.cursor <= Cursor(other).cursor
  def __ge__(self, other): return self.cursor >= Cursor(other).cursor
  def __lt__(self, other): return self.cursor < Cursor(other).cursor
  def __gt__(self, other): return self.cursor > Cursor(other).cursor

  @property
  def source(self):
    return ''.join([t.spelling for t in self.tokens])

def cursorize(cursor):
  cursor = getattr(cursor, 'cursor', cursor)
  yield Cursor(cursor)
  for child in cursor.get_children():
    for c in cursorize(child):
      yield c


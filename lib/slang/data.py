from clang import cindex
from fnmatch import fnmatch
import os
import sys
import warnings

# These can be quite large.
CACHE_AST_FILES = False

# Ignore include directives, since they are not necessary and slow down
# extraction tremendously.
DEFAULT_ARGS = ['-nostdinc', '-nostdinc++']

def parseDirectory(dirname, glob='*.[ch]pp', args=DEFAULT_ARGS, xargs=[]):
  args = args + xargs
  for dirpath,_,filenames in os.walk(dirname):
    for filename in filenames:
      abspath = os.path.join(dirpath, filename)
      if not fnmatch(abspath, glob):
        continue
      tu = parse(abspath, args, xargs)
      if tu is not None:
        yield tu

def parse(filename, args=DEFAULT_ARGS, xargs=[]):
  index = cindex.Index.create()
  astpath = filename + '.ast'
  if os.path.isfile(astpath):
    return index.read(astpath)
  else:
    try:
      tu = index.parse(filename, args=args)
    except:
      warnings.warn('Failed to parse %s' % filename)
      return None
    if CACHE_AST_FILES:
      tu.save(astpath)
    return tu

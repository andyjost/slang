#!//usr/bin/env python2
# exec /usr/bin/env python2 -i -m slang.tokenize foo.hpp

from clang import cindex
from clang.cindex import TokenKind, CursorKind
from slang.data import parseDirectory
from slang.tokenize import cursorize, dumpSource, filterCursorsByFilename, tokenize
from fnmatch import fnmatch
from itertools import ifilter, islice
import textwrap
import cStringIO
import sys
import numpy as np
import re


function_kinds = {
    CursorKind.FUNCTION_TEMPLATE
  , CursorKind.FUNCTION_DECL
  , CursorKind.CXX_METHOD
  , CursorKind.CONSTRUCTOR
  , CursorKind.DESTRUCTOR
  , CursorKind.CONVERSION_FUNCTION
  }

dirname = sys.argv[1]
pattern = dirname + '.*' + \
    ('' if dirname.endswith('pp') else '\.[ch]pp$')

def get_cursors(tu):
  cursors = cursorize(tu.cursor)
  cursors = filterCursorsByFilename(
      cursors, lambda filename: re.match(pattern, filename)
    )
  cursors = ifilter(lambda cursor: cursor.kind in function_kinds, cursors)
  return cursors

# for tu in islice(parseDirectory('boost/python'), 10000):
for tu in parseDirectory(sys.argv[1]):
  # print tu
  for cursor in get_cursors(tu):
    if cursor.kind in function_kinds:
      # print cursor, cursor.location
      text = [tok.spelling for tok in tokenize(cursor)]
      stream = cStringIO.StringIO()
      dumpSource(cursor, stream=stream)
      stream.seek(0)
      sys.stdout.write(stream.readline())
      lines_no_pp = [
          line for line in stream.readlines()
              if not line.startswith('#')
        ]
      sys.stdout.write(textwrap.dedent(''.join(lines_no_pp)))
      import code
      code.interact(local=locals())
      print


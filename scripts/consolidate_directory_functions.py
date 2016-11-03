#!/usr/bin/env python

from clang.cindex import TokenKind, CursorKind
from itertools import ifilter
from slang.data import parseDirectory
from slang.tokenize import cursorize, dumpSource, filterCursorsByFilename, FUNCTION_KINDS
import re
import sys

dirname = sys.argv[1]
pattern = dirname + '.*' + \
    ('' if dirname.endswith('pp') else '\.[ch]pp$')

def get_cursors(tu):
  cursors = cursorize(tu.cursor)
  cursors = filterCursorsByFilename(
      cursors, lambda filename: re.match(pattern, filename)
    )
  cursors = ifilter(lambda cursor: cursor.kind in FUNCTION_KINDS, cursors)
  return cursors

for tu in parseDirectory(sys.argv[1], xargs=['-I.']):
  for cursor in get_cursors(tu):
    # Only consider functions with bodies.
    children = list(cursor.get_children())
    if children and children[-1].kind == CursorKind.COMPOUND_STMT:
      dumpSource(cursor, include_predent=True, strip_trailing_whitespace=True)
      print

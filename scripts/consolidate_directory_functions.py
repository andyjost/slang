#!/usr/bin/env python

from clang.cindex import TokenKind, CursorKind
from itertools import ifilter
from slang.data import parseDirectory, selectCursors
from slang.tokenize import dumpSource, filterCursorsByFilename, FUNCTION_KINDS
import re
import sys

dirname = sys.argv[1]
pattern = dirname + '.*' + \
    ('' if dirname.endswith('pp') else '\.[ch]pp$')

for tu in parseDirectory(sys.argv[1], args=['-I.']):

  for cursor in selectCursors(tu, [data.is_function_with_body], pattern):
    # children = list(cursor.get_children())
    # if children and children[-1].kind == CursorKind.COMPOUND_STMT:
    dumpSource(cursor, include_predent=True, strip_trailing_whitespace=True)
    print

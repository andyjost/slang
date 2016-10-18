#!/usr/bin/env python2

# USAGE: $0 <num> dirname

# A script for demonstrating data input.  Picks a few source files from the given
# directory, parses, indexes, and then dumps the token stream.

# from clang import cindex
# import os
import sys
from slang import data, tokenize

for topdir in sys.argv[2:]:
  # The number of files to process from each directory.
  N = int(sys.argv[1])
  i = 0
  for tu in data.parseDirectory(topdir):
    tokenize.dumpTokens(tu.cursor)
    i += 1
    if i >= N: break


# for dirpath,_,filenames in os.walk(sys.argv[1]):
#   for filename in filenames:
#     index = cindex.Index.create()
#     abspath = os.path.join(dirpath, filename)
#     tu = index.parse(abspath)
#     tu.save(abspath + '.ast')

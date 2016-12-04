#!/usr/bin/env python
from clang.cindex import CursorKind, TokenKind
from itertools import *
from sklearn.naive_bayes import *
from slang.analysis import *
from slang.data import *
from slang.functors import *
from slang.line import Line
from slang.tokenize import *
from slang.genetic import *
import collections
import numpy as np
import operator
import pdb
import sys
import code

files = ['./boost/optional/']
# files = ['./boost/optional/', './boost/numeric/conversion/']
# files = ['./boost/accumulators/']
# files = [f.strip() for f in open('boost_files.txt.a-c').readlines()]
idx = SourceIndex(files, args=['-I.'])
cursors = np.array(list(idx.cursors([is_definition])))
print cursors.size

d = down(_, 2)
def xf(seq):
  seq[1] = 3
d2 = functor.rebind(d, 3)


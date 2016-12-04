#!/usr/bin/env python
from clang.cindex import CursorKind, TokenKind
from itertools import *
from sklearn.naive_bayes import *
from slang.analysis import *
from slang.data import *
from slang.functors import *
from slang.line import Line
from slang.tokenize import *
import collections
import numpy as np
import operator
import pdb
import sys
import code

def pause():
  # sys.stdout.write('[Press enter to continue]')
  # sys.stdin.readline()
  code.interact(local=globals(), banner='')
  return

def interact(): pdb.set_trace()

def pp(seq):
  for x in seq: print x

positive = []
def getpos(item):
  positive.append(item)
  # print item.kind
  # pdb.set_trace()

negative = []
def getneg(item):
  negative.append(item)
  # pdb.set_trace()

def fst(s): return s[0]

getters = dict(on_true=getpos, on_false=getneg)

print 'Classify on property "a newline occurs before the function body."'
files = ['./boost/optional/', './boost/numeric/conversion/']
# files = ['./boost/accumulators/']
# files = [f.strip() for f in open('boost_files.txt.a-c').readlines()]
idx = SourceIndex(files, args=['-I.'])
cursors = np.array(list(idx.cursors([is_definition])))
print '# of function definitions:', len(cursors)
def p(out=None, given=true):
  positive[:] = []
  negative[:] = []
  prob = probability(cursors, function_has_newline_before_body, given, **getters)
  if out:
    print >>out, 'P=', prob
    print >>out, "POSITIVE:"
    for item in positive:
      print >>out, item
    print >>out, ''
    print >>out, "NEGATIVE:"
    for item in negative:
      print >>out, item
  return prob

def e(given=true):
  return gain(cursors, function_has_newline_before_body, given)

RULE = (
    (
        is_constructor
      | is_kind(_, CursorKind.CXX_METHOD)
      | is_kind(_, CursorKind.DESTRUCTOR)
      | is_kind(_, CursorKind.CONVERSION_FUNCTION)
      )
  & ~contains_keyword(function_body, 'if')
  & lt(function_body_stmts, 3)
  & lt(length_as_single_line, 115)
  )
print 'P =', probability(cursors, function_has_newline_before_body)
print 'P|R =', probability(cursors, function_has_newline_before_body, RULE)
print 'P|~R =', probability(cursors, function_has_newline_before_body, ~RULE)
print 'E(R) =', gain(cursors, function_has_newline_before_body, RULE)

FEATURES = [
    is_constructor
  , is_kind(_, CursorKind.CXX_METHOD)
  , is_kind(_, CursorKind.DESTRUCTOR)
  , is_kind(_, CursorKind.CONVERSION_FUNCTION)
  , contains_keyword(function_body, 'if')
  , function_body_stmts
  , length_as_single_line
  ]

data = np.array([[f(c) for f in FEATURES] for c in cursors])
target = np.array(map(function_has_newline_before_body, cursors))
# data.dump('data.np')
# target.dump('target.np')
pause()

print
print '=' * 80
print 'Naive Bayes (1)'.center(80)
print '=' * 80

for nb in [GaussianNB(), BernoulliNB(), MultinomialNB()]:
  y_pred = nb.fit(data, target).predict(data)
  print "%s: mislabeled %d/%d points." % (
      type(nb).__name__
    , (target != y_pred).sum()
    , data.shape[0]
    )

pause()

mislabeled = [(c,d) for c,t,p,d in izip(cursors, target, y_pred, data) if t != p]
print
print 'Mislabeled example:'
miss,datum = mislabeled[2]
print datum
print
print miss.source

pause()

print
print '=' * 80
print 'Naive Bayes (2)'.center(80)
print '=' * 80
print 'With line length thresholding.'

best_missed = float('inf')
for thresh in xrange(100, 135, 5):
  FEATURES = [
      is_constructor
    , is_kind(_, CursorKind.CXX_METHOD)
    , is_kind(_, CursorKind.DESTRUCTOR)
    , is_kind(_, CursorKind.CONVERSION_FUNCTION)
    , contains_keyword(function_body, 'if')
    , function_body_stmts
    , lt(length_as_single_line, thresh)
    ]
  data_ = np.array([[f(c) for f in FEATURES] for c in cursors])
  target_ = np.array(map(function_has_newline_before_body, cursors))
  nb = MultinomialNB()
  y_pred_ = nb.fit(data_, target_).predict(data_)
  n_missed = (target_ != y_pred_).sum()
  print "%s(thres=%d): mislabeled %d/%d points." % (
       type(nb).__name__, thresh, n_missed, data_.shape[0]
    )
  if n_missed < best_missed:
    data,target,y_pred = data_,target_,y_pred_

pause()

print '====== MISLABELED ======'
missed = y_pred != target
imiss, = np.where(missed)
costs = np.sort(
    [[elem.dot(elem) for elem in data-a] for a in data[imiss]]
  , axis=1
  )
bests = np.min(costs,axis=1)[:,None]
for i,group in islice(groupby(izip(*np.where(costs==bests)), fst), 8, 9):
  print '[[[[Missed]]]]'
  print data[imiss[i]]
  print cursors[imiss[i]].source
  pause()
  print '[[[[Similar]]]]'
  for isimilar in islice([j for unused,j in group if j!=i and not missed[j]], 3):
    print data[isimilar]
    print cursors[isimilar].source
    pause()

print "(END)"
pause()


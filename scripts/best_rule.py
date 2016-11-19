#!/usr/bin/env python
from slang.data import *
from slang.tokenize import *
from slang.analysis import *
from slang.functors import *
import collections
from slang.line import Line
import sys
import pdb
from itertools import *
import operator

from clang.cindex import CursorKind, TokenKind

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

getters = dict(on_true=getpos, on_false=getneg)

idx = SourceIndex('./boost/optional/', args=['-I.'])
cursors = tuple(idx.cursors([is_definition]))
print '# of functions:', len(cursors)
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
  return entropic_quality(cursors, function_has_newline_before_body, given)

# print 'p|nothing', p()
# print 'p|method', p([is_kind(CursorKind.CXX_METHOD)])
# print 'p|<81&method', p([lt(length_as_single_line,80), is_kind(CursorKind.CXX_METHOD)])
# print 'p|1stmt&method', p([lt(function_body_stmts,2), is_kind(CursorKind.CXX_METHOD)])
# print 'p|!1stmt&method', p([not_(or_(lt(function_body_stmts,2), is_kind(CursorKind.CXX_METHOD)))])

RULE = (
    (
        is_constructor
      | is_kind(_, CursorKind.CXX_METHOD)
      | is_kind(_, CursorKind.DESTRUCTOR)
      | is_kind(_, CursorKind.CONVERSION_FUNCTION)
      )
  & not_(contains_keyword(function_body, 'if'))
  & lt(function_body_stmts, 3)
  & lt(length_as_single_line, 115)
  )

print 'P =', probability(cursors, function_has_newline_before_body)
print 'P|R =', probability(cursors, function_has_newline_before_body, RULE)
print 'P|~R =', probability(cursors, function_has_newline_before_body, ~RULE)
print 'E(R) =', e(RULE)


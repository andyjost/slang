from __future__ import division
from .functors import *
from itertools import *
import math
import operator
import collections

def cnf2func(cnf):
  seq = lambda x: x if isinstance(x, collections.Sequence) else [x]
  return reduce(
      operator.and_
    , (reduce(operator.or_, seq(term), true) for term in cnf)
    , true
    )

def probability(
    seq, what, given=true
  , on_true=lambda _:None, on_false=lambda _:None
  ):
  total = 0
  positive = 0
  for item in seq:
    # if all(condition(item) for condition in given):
    if given(item):
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
  if p in [0,1]: return 0
  q = 1 - p
  return (p*math.log(p) + q*math.log(q)) / -math.log(2)

def gain(seq, what, given=true, *args, **kwds):
  a = entropy(probability(seq, what, given, *args, **kwds))
  b = entropy(probability(seq, what, ~given, *args, **kwds))
  return (a + b) / 2


#!/usr/bin/env python
from clang.cindex import CursorKind, TokenKind
from itertools import *
from sklearn.naive_bayes import *
from sklearn import preprocessing
from sklearn.neural_network import MLPClassifier
from slang.analysis import *
from slang.data import *
from slang.functors import *
from slang.line import Line
from slang.tokenize import *
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import classification_report
import collections
import numpy as np
import operator
import pdb
import sys
import code

def report(classifier, data, target):
  y_pred = classifier.fit(data, target).predict(data)
  n_missed = (target != y_pred).sum()
  print "%s: mislabeled %d/%d points." % (
       type(classifier).__name__, n_missed, data.shape[0]
    )

data = np.load('data.np').astype(dtype=float)
target = np.load('target.np').astype(dtype=float)

print
print '=' * 80
print 'Naive Bayes'.center(80)
print '=' * 80
nb = MultinomialNB()
report(nb, data, target)

print
print '=' * 80
print 'Neural Net (scaled)'.center(80)
print '=' * 80
scaled_data = preprocessing.scale(data)
lpc = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(4,6), random_state=1)
report(lpc, scaled_data, target)

print
print '=' * 80
print 'Neural Net w/ Hyperparameter Tuning'.center(80)
print '=' * 80
tuned_parameters = [{
    'alpha': 10 ** -np.arange(1.,7.)
  , 'hidden_layer_sizes': list(product(range(1,10), np.arange(1,10)))
  }]
clf = GridSearchCV(lpc, tuned_parameters, cv=2, n_jobs=4, scoring='precision_macro')
report(clf, data, target)

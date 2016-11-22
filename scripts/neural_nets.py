#!/usr/bin/env python
from itertools import *
from sklearn import datasets
from sklearn import preprocessing
from sklearn import svm
from sklearn.metrics import classification_report
from sklearn.model_selection import GridSearchCV
from sklearn.naive_bayes import *
from sklearn.neural_network import MLPClassifier
import numpy as np
import warnings

warnings.simplefilter('ignore')

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
print 'SVM'.center(80)
print '=' * 80
classifier = svm.SVC()
report(classifier, data, target)

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

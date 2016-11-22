#!/usr/bin/env python
from itertools import *
from sklearn.cluster import AffinityPropagation
from sklearn import datasets
from sklearn import metrics
from sklearn import preprocessing
from sklearn.metrics import classification_report
from sklearn.model_selection import GridSearchCV
import numpy as np
import matplotlib.pyplot as plt
from itertools import cycle

data = np.load('data.np').astype(dtype=float)
target = np.load('target.np').astype(dtype=float)

print
print '=' * 80
print 'Affinity Propagation'.center(80)
print '=' * 80
data = preprocessing.scale(data)
af = AffinityPropagation(preference=-10).fit(data)
y_pred = af.predict(data)
n_missed = (target != y_pred).sum()
print "%s: mislabeled %d/%d points." % (
     type(af).__name__, n_missed, data.shape[0]
  )
cluster_centers_indices = af.cluster_centers_indices_
labels = af.labels_
n_clusters_ = len(cluster_centers_indices)
print('Estimated number of clusters: %d' % n_clusters_)
print("Homogeneity: %0.3f" % metrics.homogeneity_score(target, labels))
print("Completeness: %0.3f" % metrics.completeness_score(target, labels))
print("V-measure: %0.3f" % metrics.v_measure_score(target, labels))
print("Adjusted Rand Index: %0.3f"
      % metrics.adjusted_rand_score(target, labels))
print("Adjusted Mutual Information: %0.3f"
      % metrics.adjusted_mutual_info_score(target, labels))
print("Silhouette Coefficient: %0.3f"
      % metrics.silhouette_score(data, labels, metric='sqeuclidean'))

plt.close('all')
plt.figure(1)
plt.clf()

colors = cycle('bgrcmykbgrcmykbgrcmykbgrcmyk')
for k, col in zip(range(n_clusters_), colors):
    class_members = labels == k
    cluster_center = data[cluster_centers_indices[k]]
    plt.plot(data[class_members, 0], data[class_members, 1], col + '.')
    plt.plot(cluster_center[0], cluster_center[1], 'o', markerfacecolor=col,
             markeredgecolor='k', markersize=14)
    for x in data[class_members]:
        plt.plot([cluster_center[0], x[0]], [cluster_center[1], x[1]], col)

plt.title('Estimated number of clusters: %d' % n_clusters_)
plt.show()

# print
# print '=' * 80
# print 'Neural Net w/ Hyperparameter Tuning'.center(80)
# print '=' * 80
# tuned_parameters = [{
#     'alpha': 10 ** -np.arange(1.,7.)
#   , 'hidden_layer_sizes': list(product(range(1,10), np.arange(1,10)))
#   }]
# clf = GridSearchCV(estimator, tuned_parameters, cv=2, n_jobs=4, scoring='precision_macro')
# report(clf, data, target)

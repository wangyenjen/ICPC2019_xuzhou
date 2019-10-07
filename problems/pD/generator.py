#!/usr/bin/env python3

import sys, os
os.environ['OMP_NUM_THREADS'] = '2'

import numpy as np
from scipy.spatial import ConvexHull

Z = int(sys.argv[1])
R = int(sys.argv[2])
K = int(sys.argv[3])
np.random.seed(Z * 185 + K * 3918592 + R)

N = Z * 17

# generate random points on sphere
elev = np.arcsin(np.random.random(N) * 2 - 1)
azim = 2 * np.pi * np.random.random(N)
radi = R * 0.99 + (R * 0.01) * np.random.random(N)

pts = np.empty((N, 3))
pts[:,0] = radi * np.cos(elev)
pts[:,1] = pts[:,0]
pts[:,2] = radi * np.sin(elev)
pts[:,0] *= np.cos(azim)
pts[:,1] *= np.sin(azim)

# k, theta: rotation axis / angle
# ph: plane point & normal vector
k = pts[0] / np.linalg.norm(pts[0])
ph = pts[-K*2:]
ph /= np.linalg.norm(ph, axis = -1)[:,None]
theta = 2 * np.pi * np.random.random()

# random scaling
pts[:,0] *= 0.4 + 0.6 * np.random.random()
pts[:,1] *= 0.4 + 0.6 * np.random.random()
pts[:,2] *= 0.4 + 0.6 * np.random.random()

# random rotation
pts = pts * np.cos(theta) + np.cross(k, pts) * np.sin(theta) + \
        (np.dot(pts, k) * (1 - np.cos(theta)))[:,None] * k[None,:]
pts = pts.astype('int')

# binary search to make at most Z points on the convex hull
l, r = Z, N
while l + 1 < r:
    m = (l + r) // 2
    hull = ConvexHull(pts[:m])
    if hull.vertices.shape[0] > Z: r = m
    else: l = m
    #print('meow', file = sys.stderr)
hull = ConvexHull(pts[:l])

# remove redundant edges
ed = {}
def Add(a, b, c):
    global ed
    if a > b: a, b = b, a
    if (a, b) in ed: ed[(a, b)].append(c)
    else: ed[(a, b)] = [c]
for i in hull.simplices:
    Add(i[0], i[1], i[2])
    Add(i[1], i[2], i[0])
    Add(i[2], i[0], i[1])
lst = []
for i in ed:
    assert(len(ed[i]) == 2)
    a, b, c, d = pts[i[0]], pts[i[1]], pts[ed[i][0]], pts[ed[i][1]]
    if np.dot(np.cross(b - a, c - a), d - a) == 0: lst.append(i)
for i in lst: del ed[i]
ed = np.array([list(i) for i in ed])
vt = np.array(hull.vertices)
np.random.shuffle(ed)
np.random.shuffle(vt)
mp = {}
for j, i in enumerate(vt): mp[i] = j

# generate plane
# ax + by + cz = d (= ax0 + by0 + cz0)
qu = []
for i in range(K):
    norm = ph[i*2]
    pt = ph[i*2+1] * (np.random.random() * R * .7)
    p = np.array([norm[0], norm[1], norm[2], np.dot(norm, pt)])
    p *= ((np.random.random() * .5 + .5) * R ** 2) / np.max(np.abs(p))
    p = p.astype('int')
    qu.append(tuple(p))

print('%d %d %d' % (len(vt), len(ed), K))
for i in vt: print('%d %d %d' % tuple(pts[i]))
for i in ed: print('%d %d' % (mp[i[0]], mp[i[1]]))
for i in qu: print('%d %d %d %d' % i)

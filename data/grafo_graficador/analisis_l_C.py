import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import sys
import os
import time
import graphImportData as gid


l0 = 23.336
c0 = 0.442651428571
qs = [60*(i+1) for i in range(20)]
proms = [i for i in range(3)]

lprom = []
cprom = []

for q in qs:
	
	l = []
	c = []

	for prom in proms:
		name = "q_{0}_{1}.net".format(q,prom)
		print name
		edges = gid.loadGraphEdges(name)
		rewire = gid.loadGraphRewire(name)
		n = gid.loadGraphN(name)
		pos = gid.loadGraphPositions(n)
		g = nx.Graph(edges)
		l.append(nx.average_shortest_path_length(g)/l0)
		c.append(nx.average_clustering(g)/c0)

	lprom.append(np.mean(np.array(l)))
	cprom.append(np.mean(np.array(c)))

np.savetxt("qlc.txt", [qs,lprom,cprom], fmt = '%.8f', header='q l c')

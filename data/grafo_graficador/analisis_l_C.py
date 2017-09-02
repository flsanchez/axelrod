import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import sys
import os
import time
import graphImportData as gid

f = open("run.log")
f = f.readlines()
numOfQs = int(f[1])
numOfProms = int(f[2])
m = int(f[3])
b = int(f[4])

l0 = 23.336
c0 = 0.442651428571
qs = [m*(i+1) + b for i in range(numOfQs)]
proms = [i for i in range(numOfProms)]

lprom = []
cprom = []
cont = 1.0

for q in qs:
	
	l = []
	c = []

	for prom in proms:
		name = "q_{0}_{1}.net".format(q,prom)
		print "{0}%: {1}".format(100*cont/(len(qs)*len(proms)),name)
		edges = gid.loadGraphEdges(name)
		rewire = gid.loadGraphRewire(name)
		n = gid.loadGraphN(name)
		pos = gid.loadGraphPositions(n)
		g = nx.Graph(edges)
		l.append(nx.average_shortest_path_length(g)/l0)
		c.append(nx.average_clustering(g)/c0)
		cont = cont + 1

	lprom.append(np.mean(np.array(l)))
	cprom.append(np.mean(np.array(c)))

np.savetxt("qlc.txt", [qs,lprom,cprom], fmt = '%.8f', header='q l c')

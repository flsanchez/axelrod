import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import graphImportData as gid
import sys

name = sys.argv[1]
edges = gid.loadGraphEdges(name)
rewire = gid.loadGraphRewire(name)
n = gid.loadGraphN(name)
pos = gid.loadGraphPositions(n)

g = nx.Graph(edges)
gRew = nx.Graph(rewire)
print nx.number_of_edges(g)
print nx.number_of_edges(gRew)

gid.graphPlot(gRew,n,1)
#nx.draw(g,pos,edge_color = 'r',node_size=50)
#plt.show()
#plt.figure(figsize=(12,12))
"""a = np.array([(i,j) for i in range(n) for j in range(n)])
a = zip(*a)
plt.plot(a[0],a[1],'k.',ms=2)
nx.draw(gRew,pos,edge_color = 'g',node_size=50)
plt.show()"""

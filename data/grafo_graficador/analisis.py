import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import sys
import graphImportData as gid

name = sys.argv[1]
edges = gid.loadGraphEdges(name)
rewire = gid.loadGraphRewire(name)
n = gid.loadGraphN(name)
pos = gid.loadGraphPositions(n)

g = nx.Graph(edges)
gRew = nx.Graph(rewire)

print nx.number_of_edges(g)
print nx.number_of_edges(gRew)

"""nx.draw(g,pos,edge_color = 'r',node_size=50)
plt.show()
nx.draw(gRew,pos,edge_color = 'g',node_size=50)
plt.show()"""


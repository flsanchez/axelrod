import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import sys

f = open(sys.argv[1],'r')
data = [ [ j for j in line[:-2].split(" ")] for line in f] #el line[:-2] es para sacarme de encima el " \n"
edges={j: [ int(i.split(",")[0]) for i in data[j] ] for j in range(len(data))}

edgesRewire = []

for i in range(len(data)):
	for j in data[i]:
		if(int(j.split(",")[1]) == 1):
			edgesRewire.append( ( i, int(j.split(",")[0]) ) )
	
pos = {j: [] for j in range(len(edges))}

s = 1
n = int(len(pos)**0.5)
for i in range(n):
	for j in range(n):
		pos[i*n+j] = [i*s,j*s]
		
#edgesTuple = [ (j,i) for j in edges for i in edges[j] ]
G=nx.from_dict_of_lists(edges)
Grew = nx.DiGraph(edgesRewire)
edgesTuple = G.edges()
edgesList = [x for x in edgesTuple if x not in edgesRewire]
nx.draw(G,pos,edgelist = edgesList,node_size=50)
nx.draw(Grew,pos,arrow = True,edgelist = edgesRewire,edge_color = 'r',node_size=50)
plt.show()


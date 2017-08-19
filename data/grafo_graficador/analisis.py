import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import sys
import os
import graphImportData as gid


cwd=os.getcwd()
ls=os.listdir(cwd)
ls = [sys.argv[1]]

for files in ls:
	if files.endswith(".txt"):
		name = files
		edges = gid.loadGraphEdges(name)
		#rewire = gid.loadGraphRewire(name)
		n = gid.loadGraphN(name)
		pos = gid.loadGraphPositions(n)

		g = nx.Graph(edges)
		#gRew = nx.Graph(rewire)

		print "Links Totales: {0}".format(nx.number_of_edges(g))
		#print "Links de rewiring: {0}".format(nx.number_of_edges(gRew))
		print "Camino minimo medio: {0}".format(nx.average_shortest_path_length(g)/23.336)
		print "Clustering medio: {0}".format(nx.average_clustering(g)/0.442651428571)

		plt.plot(nx.degree_histogram(g),'ro-')
		#nx.draw(g,pos)
		plt.show()

		#nx.draw(g,pos,edge_color = 'r',node_size=50)
		#plt.show()
		#print nx.number_of_edges(gRew)
		#nx.draw(gRew,pos,edge_color = 'g',node_size=50)
		#plt.show()


import matplotlib.pyplot as plt
import numpy as np
import networkx as nx

def loadGraphEdges(name):
	with open(name) as f:
		for i in range(2):
			f.readline()
		data = f.readline()
		data = data.rstrip(" \n").lstrip("edges ").split(" ")
		edges = [ ( int(tup.split(",")[0]) , int(tup.split(",")[1]) ) for tup in data ]
	return edges

def loadGraphRewire(name):
	with open(name) as f:
		for i in range(4):
			f.readline()
		data = f.readline()
		data = data.rstrip(" \n").lstrip("rewire ").split(" ")
		if(len(data) > 1):
			rewire = [ ( int(tup.split(",")[0]) , int(tup.split(",")[1]) ) for tup in data ]
			return rewire
		else:
			return []

def loadGraphN(name):
	with open(name) as f:
		n = int(f.readline().rstrip('\n').lstrip('N '))
	return n

def loadGraphPositions(n):
	pos = {j: [] for j in range(n**2)}

	s = 1
	for i in range(n):
		for j in range(n):
			pos[i*n+j] = [i*s,j*s]
	
	return pos

def edgesResta(edgesIni,edgesFin):
	edgesRestaV = []
	for fin in edgesFin:
		flag = 0
		for ini in edgesIni:
			if ini == fin:
				flag = 1
		if flag == 0:
			edgesRestaV.append(fin)
	return edgesRestaV

def graphPlot(graph,n,show):
	plt.figure(figsize=(12,12))
	pos = loadGraphPositions(n)
	a = np.array([(i,j) for i in range(n) for j in range(n)])
	a = zip(*a)
	plt.plot(a[0],a[1],'k.',ms=2)
	nx.draw(graph,pos,edge_color = 'g',node_size=50)
	if show == 1:
		plt.show()

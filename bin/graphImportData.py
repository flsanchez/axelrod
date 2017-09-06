def loadGraphEdges(name):
	f = open(name,'r')
	n = int(f.readline().split(" ")[-1])
	f = f.read()
	data = f.split(" \n")[0]
	edges = []
	for tup in data.split(" "):
		edges.append( ( int(tup.split(",")[0]) , int(tup.split(",")[1]) ) )
	return edges

def loadGraphRewire(name):
	f = open(name,'r')
	n = int(f.readline().split(" ")[-1])
	f = f.read()
	data = f.split(" \n")[1]
	rewire = []
	for tup in data.split(" "):
		rewire.append( ( int(tup.split(",")[0]) , int(tup.split(",")[1]) ) )
	return rewire

def loadGraphN(name):
	f = open(name,'r')
	n = int(f.readline().split(" ")[-1])
	return n

def loadGraphPositions(n):
	pos = {j: [] for j in range(n**2)}

	s = 1
	for i in range(n):
		for j in range(n):
			pos[i*n+j] = [i*s,j*s]
	
	return pos

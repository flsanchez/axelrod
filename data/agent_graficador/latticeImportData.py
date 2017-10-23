import numpy as np
import matplotlib.pyplot as plt

def latticeReadLine(line):
	data = line.rstrip(" \n").split(" ")
	agents = [ [int(trait) for trait in agent.split(",")] for agent in data]
	return agents

def latticeGetAgents(name):
	with open(name) as f:
		for i in range(0,6):
			f.readline()
		data = f.readline()
		data = data.rstrip("\n").lstrip("feat ").split(" ")
		agents = [ [int(trait) for trait in agent.split(",")] for agent in data]
	return agents

def latticeGetLabels(name):
	with open(name) as f:
		for i in range(0,4):
			f.readline()
		data = f.readline()
		data = data.rstrip("\n").lstrip("label ").split(" ")
		labels = [ int(label) for label in data]
	return labels

def latticeFixLabels(labels):
	n = len(labels)
	labelsExist = [ 0 for i in range(0,n) ]
	#setteo las posiciones de labelsExist a 1 si hay una etiqueta
	#en esa posicion
	for label in labels:
		labelsExist[label] = 1
	cont = 1
	#donde la etiqueta exista, reenumero secuencialmente
	for i in range(1,n):
		if(labelsExist[i] == 1):
			labelsExist[i] = cont
			cont += 1
	#reenumero el vector de labels
	for i in range(0,n):
		labels[i] = labelsExist[labels[i]] 

def latticeGetStubs(name):
	with open(name) as f:
		for i in range(0,5):
			f.readline()
		data = f.readline()
		data = data.rstrip("\n").lstrip("stub ").split(" ")
		stubs = [ int(stub) for stub in data]
	return stubs

def latticeBaseQ(agents, q):
	baseQ = np.zeros(len(agents))
	qList = np.array([q**i for i in range(len(agents[0])-1)])
	for i in range(len(agents)):
		baseQ[i] = np.sum(np.array(agents[i][0:-1])*qList)
	return baseQ

def latticeBaseQFile(name, q):
	res = []
	cont = 0
	with open(name,'r') as f:
		for lines in f:
			print cont
			res.append(latticeBaseQ(latticeRead(lines),q))
			cont = cont+1
	return res

def latticeFeatN(agents,feat):
	featn = np.array([agent[feat] for agent in agents])
	return featn

def latticeShowLabels(name,show):
	labels = np.array(latticeGetLabels(name))
	n = int(len(labels)**0.5)
	z = labels.reshape((n,n))
	cMap = 'hsv'
	plt.figure()
	plt.imshow(z,interpolation='nearest',
						cmap = cMap, origin='upper', vmin=np.min(z), vmax=np.max(z))
	plt.colorbar()
	if show == 1:
		plt.show()

def latticeShowFeatNEqualsTo(name,show,feat,eqt):
	agents = latticeGetAgents(name)
	feat = 10
	vacFeat = latticeFeatN(agents,feat)
	n = int(len(vacFeat)**0.5)
	z = [ 0 for i in range(0,n*n) ]
	for i in range(0,n*n):
		if vacFeat[i] == eqt:
			z[i] = 1
	z = np.array(z)
	z = z.reshape((n,n))
	cMap = 'seismic'
	plt.figure()
	plt.imshow(z,interpolation='nearest',
						cmap = cMap, origin='upper', vmin=np.min(z), vmax=np.max(z))
	plt.colorbar()
	if show == 1:
		plt.show()

def latticeShowStub(name,show):
	stubs = np.array(latticeGetStubs(name))
	n = int(len(stubs)**0.5)
	z = stubs.reshape((n,n))
	cMap = 'seismic'
	plt.figure()
	plt.imshow(z,interpolation='nearest',
						cmap = cMap, origin='upper', vmin=np.min(z), vmax=np.max(z))
	plt.colorbar()
	if show == 1:
		plt.show()
	

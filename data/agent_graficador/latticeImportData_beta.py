import numpy as np

def latticeReadLine(line):
	data = line.rstrip(" \n").split(" ")
	agents = [ [int(trait) for trait in agent.split(",")] for agent in data]
	return agents

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
			
	

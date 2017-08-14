import numpy as np
import matplotlib.pyplot as plt
import sys
import os

cwd=os.getcwd()
ls=os.listdir(cwd)
q=0

for files in ls:
	if files.endswith(".txt"):
		
		print files
		f = open(files,'r')
		#q = f.readline()
		#q = int(q.split(" ")[-1].split("=")[-1])
		q = q+1
		data = [int(i) for i in f if i[0] != '#']
		f = open(files,'r')
		stop = f.read()
		stop = int(stop.split("\n")[-2].split("=")[-1])
		nmbr = 0
		y = []
		x = []

		
		
		"""for i in range(len(data)-1):
			x = x + [data[i],data[i+1]-1]

		for i in range(len(data)-1):
			y = y + [nmbr]*2
			nmbr = nmbr + 1

		x = np.array(x)
		y = np.array(y)"""

		x = np.array(data)
		y = np.arange(len(data))
		 
		plt.plot(x,y,'b')
		plt.plot([stop, stop], [0, np.max(y)],'r',label="Paso = {0}".format(stop))
		plt.legend(loc='lower right')
		plt.xlabel("Pasos")
		plt.ylabel("Rewires Aceptados")
		plt.title("Rewires Aceptados para q = {0}".format(q))
		plt.savefig("SerieTemporal_rewireAcep_q{0}.png".format(q))
		plt.clf()
		#plt.show()
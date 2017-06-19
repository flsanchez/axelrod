import matplotlib.pyplot as plt
import sys
import numpy as np
import os

cwd=os.getcwd()
ls=os.listdir(cwd)


for files in ls:
	if files.endswith(".txt"):

		fopen = open(files,'r')
		fopen.readline()
		aux = fopen.readline()
		aux = aux.split(" ")
		n = int(aux[1])
		f = int(aux[2])
		q = int(aux[3])
		paso = int(aux[4])

		fopen.close()

		data = np.loadtxt(files,unpack=True)

		minbin=np.min(data)/paso*10
		maxbin=np.max(data)/paso*10
		binpos=np.arange(minbin,maxbin+1,2000)
		mu = np.sum(data)/np.size(data)/paso*10
		print mu

		plt.hist(data/paso*10,bins=binpos)
		plt.show()

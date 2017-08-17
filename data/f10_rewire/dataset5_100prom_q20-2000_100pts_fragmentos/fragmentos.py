import matplotlib.pyplot as plt
import sys
import numpy as np
import os

cwd=os.getcwd()
ls=os.listdir(cwd)

for files in ls:
	if files.endswith(".frag"):

		f = open(files,'r')
		f.readline()
		aux = f.readline()
		aux = aux.split(" ")
		n = int(aux[1])
		q = int(aux[3])
		f.close()

		size, freq = np.loadtxt(files,unpack=True)
		
plt.plot(np.log(size),np.log(freq),'ro');
plt.show()

import matplotlib.pyplot as plt
import sys
import numpy as np
import os

cwd=os.getcwd()
ls=os.listdir(cwd)

Smax = np.array([])
var = np.array([])
q = np.array([])

for files in ls:
	if files.endswith(".txt"):

		f = open(files,'r')
		f.readline()
		aux = f.readline()
		aux = aux.split(" ")
		n = int(aux[1])
		q = np.append(q, int(aux[3]))
		f.close()

		data = np.loadtxt(files,unpack=True)

		data = data[2]

		mu = np.sum(data)/np.size(data)

		Smax = np.append(Smax, mu)

		sigma2= np.sum(data*data)/np.size(data) - mu**2

		var = np.append(var, np.sqrt(sigma2))
					
ax=plt.axes()
ax.errorbar(q,Smax,yerr=var,marker='s',linestyle='None')
ax.set_title("Rewires Aceptados  vs. q")
ax.set_xlabel("q")
ax.set_xlim((np.min(q),np.max(q)))
ax.set_ylabel("Rewires Aceptados")
plt.savefig("rewAcept_vs_q.png")
plt.show()

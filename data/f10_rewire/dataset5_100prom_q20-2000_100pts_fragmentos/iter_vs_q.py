import matplotlib.pyplot as plt
import sys
import numpy as np
import os

cwd=os.getcwd()
ls=os.listdir(cwd)

pasos = np.array([])
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

		data = data[1]

		mu = np.sum(data)/np.size(data)

		pasos = np.append(pasos, mu)

		sigma2= np.sum(data*data)/np.size(data) - mu**2

		var = np.append(var, np.sqrt(sigma2))
					
ax=plt.axes()
ax.errorbar(q,pasos,yerr=var,marker='s',linestyle='None')
ax.legend(loc='best')
ax.set_title("$Iteraciones$  vs. $q$")
ax.set_xlabel("q")
ax.set_ylabel("$Iteraciones$")
plt.savefig("Iter_vs_q.png")
plt.show()

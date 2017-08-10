import matplotlib.pyplot as plt
import sys
import numpy as np
import os

cwd=os.getcwd()
ls=os.listdir(cwd)

Smax = np.array([1])
var = np.array([0])
q = np.array([1])

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

		data = data / n**2

		mu = np.sum(data)/np.size(data)

		Smax = np.append(Smax, mu)

		sigma2= np.sum(data*data)/np.size(data) - mu**2

		var = np.append(var, np.sqrt(sigma2))

		mini = 1
		for i in range(len(Smax)):
			if np.abs(Smax[i]-0.5)<np.abs(mini-0.5):
				mini = Smax[i]
					
qMin = int(q[np.where(mini == Smax)])
ax=plt.axes()
ax.errorbar(q,Smax,yerr=var,marker='s',linestyle='None')
ax.plot([qMin, qMin], [0,1], 'r', label="q = {i}".format(i=qMin))
ax.legend(loc='best')
ax.set_title("$<S_{max}>/N$  vs. $q$")
ax.set_xlabel("q")
ax.set_xlim((np.min(q),np.max(q)))
ax.set_ylabel("$<S_{max}>/N$")
plt.show()

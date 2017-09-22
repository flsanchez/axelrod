import matplotlib.pyplot as plt
import numpy as np
import sys
import os

nonVac = np.loadtxt(sys.argv[1])
cMap = 'hot'

with open(sys.argv[1]) as f:
	f.readline()
	aux = f.readline()
	aux = aux.split(" ")
	n = int(aux[1])
	q = int(aux[2])
	prom = int(aux[3])
	phi = float(aux[4])

z = nonVac.reshape((n,n))
img = plt.imshow(z,interpolation='nearest',
		                cmap = cMap,
		                origin='upper',vmin=0,vmax=np.max(nonVac))

plt.colorbar(img,cmap=cMap)

plt.title("No Vacunadores; q = {0}; $\phi$ = {1}".format(q,phi))
plt.savefig("heatMapNonVac_phi_{0}.png".format(phi))

plt.show()

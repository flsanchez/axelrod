import matplotlib as mpl
from matplotlib import pyplot
import numpy as np
import sys
import os
import math as mt

niter=100000
cwd=os.getcwd()
ls=os.listdir(cwd)
cm = 'gist_rainbow'
cont=1.0
paso=100

for files in ls:
	if files.endswith(".txt"):

		print(str(cont*100/(len(ls)-2)) + "%")
		aux=int(files[0:-4])
		name=aux*paso
		fig = pyplot.figure(1)
		data = np.loadtxt(files)

		img2 = pyplot.imshow(data,interpolation='nearest',
						            cmap = cm,
						            origin='upper',vmin=0,vmax=99999)

		pyplot.colorbar(img2,cmap = cm)
		fig.suptitle("n = "+str(name))
		fig.savefig(str(name/paso)+".png")
		fig.clear()
		cont = cont+1

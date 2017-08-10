import matplotlib as mpl
from matplotlib import pyplot
import numpy as np
import sys
import os, glob
import math as mt

cwd=os.getcwd()
ls=os.listdir(cwd)
cm = 'gist_rainbow'
cont=1
total=len(glob.glob1(cwd,"*.txt"))

for files in ls:
	if files.endswith(".txt"):

		print(str(cont*100.0/total) + "%")

		fopen = open(files,'r')

		fopen.readline()
		paso = fopen.readline()
		paso = paso.split(" ")
		paso = int(paso[1])

		fopen.readline()
		aux = fopen.readline()
		aux = aux.split(" ")
		n = int(aux[1])
		f = int(aux[2])
		q = int(aux[3])

		fopen.close()

		num=int(files[0:-4])
		name=num*paso
		maxval=q**f-1
	
		fig = pyplot.figure(1)
		data = np.loadtxt(files,dtype=np.float64)
		data = data/np.max(data)

		img2 = pyplot.imshow(data,interpolation='nearest',
						            cmap = cm,
						            origin='upper',vmin=0,vmax=1)

		pyplot.colorbar(img2,cmap = cm)
		fig.suptitle("q = " + str(q) +"; tiempo = " +str(name))
		fig.savefig(str(num)+".png")
		fig.clear()
		cont = cont+1

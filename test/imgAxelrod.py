import matplotlib as mpl
from matplotlib import pyplot
import numpy as np
import sys
import os

cwd=os.getcwd()
ls=os.listdir(cwd)

for files in ls:
	if files.endswith(".txt"):

		fig = pyplot.figure(1)
		zvals = np.loadtxt(files)

		cmap2 = mpl.colors.LinearSegmentedColormap.from_list('my_colormap',
				                                       ['black','white'],
				                                       20000)

		img2 = pyplot.imshow(zvals,interpolation='nearest',
				                cmap = cmap2,
				                origin='lower')

		pyplot.colorbar(img2,cmap=cmap2)

		fig.savefig(files+".png")
		fig.clear()

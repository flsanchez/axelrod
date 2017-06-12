import matplotlib as mpl
from matplotlib import pyplot
import numpy as np
import sys
import os

zvals = np.loadtxt(sys.argv[1])

# make a color map of fixed colors
cmap = mpl.colors.ListedColormap(['black','white'])
bounds=[0,50000,99999]
norm = mpl.colors.BoundaryNorm(bounds, cmap.N)

cmap2 = mpl.colors.LinearSegmentedColormap.from_list('my_colormap',
		                                       ['black','white'],
		                                       99999)

img2 = pyplot.imshow(zvals,interpolation='nearest',
		                cmap = cmap2,
		                origin='lower')

pyplot.colorbar(img2,cmap=cmap2)

pyplot.show()
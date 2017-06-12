import matplotlib as mpl
from matplotlib import pyplot
import numpy as np
import sys
import os

zvals = np.loadtxt(sys.argv[1])

img2 = pyplot.imshow(zvals,interpolation='nearest',
		                cmap = 'gray',
		                origin='upper',vmin=0,vmax=99999)

pyplot.colorbar(img2,cmap='gray')

pyplot.show()
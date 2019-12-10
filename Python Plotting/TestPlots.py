import matplotlib.pyplot as plt
import numpy as np
import math
import csv
from matplotlib import rcParams
rcParams.update({'figure.autolayout': True})

from tkinter import *
from tkinter.ttk import *
from tkinter.filedialog import askopenfile

root = Tk()
root.withdraw()

def get_file():
	return askopenfile(mode = 'r', filetypes = [('CSV Files', '*.csv')], title = 'Choose your data file to plot')
filename = get_file().name

#https://janakiev.com/blog/csv-in-python/
#https://www.dataquest.io/blog/numpy-tutorial-python/
data = np.genfromtxt(filename, delimiter=',', dtype = 'float', names=True, skip_header=1)

indexes = range(1, data['AUX_0'].size+1)


#see validating names section of this page: '-' gets removed: https://numpy.org/devdocs/user/basics.io.genfromtxt.html
print (data["32TP"])
# Plot the data
fig, ax = plt.subplots()
ax.plot(indexes, data['43TP'], 'b-', label = 'Interior Cell')
ax.plot(indexes, data['11TP'], 'r-', label = 'Corner Cell')
plt.legend(loc = 'best')
plt.xlabel('Time (s)')
plt.ylabel('Temperature (C)')
plt.title('MSXIV Prototype Module under 100A Discharge - No Cooling')
plt.grid()
plt.show()
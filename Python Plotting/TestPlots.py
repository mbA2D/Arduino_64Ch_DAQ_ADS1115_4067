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

#number of data points
indexes = np.arange(0, data['AUX_0'].size)

'''
# This section plots a graph of two different temperatures on the same axes.

#see validating names section of this page: '-' gets removed: https://numpy.org/devdocs/user/basics.io.genfromtxt.html
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
'''

'''
# This section will hopefully create a heat map of our battery module
cell_temps = np.zeros((indexes.size, 8, 6))

#fill the cell temps
for index in indexes:
	for width in np.arange(0, 4):
		for length in np.arange(0, 3):
			cell_temps[index][width][length] = data[f'{width+1}{length+1}TP'][index]
			cell_temps[index][width][5-length] = data[f'{width+1}{length+1}TP'][index]
	for width in np.arange(4, 8):
		for length in np.arange(0, 3):
			cell_temps[index][width][length] = data[f'{width+1}{length+1}TN'][index]
			cell_temps[index][width][5-length] = data[f'{width+1}{length+1}TN'][index]
			
#the array should now be filled with our values.
print(cell_temps[2200])


air_temps = np.zeros((indexes.size, 9))

for index in indexes:
	for loc in np.arange(0, 9):
		air_temps[index][loc] = data[f'MODULE_AIR_T{loc+1}'][index]

print(air_temps[2200])

fig, ax = plt.subplots()

im = ax.pcolormesh(cell_temps[2200])
fig.colorbar(im)
ax.set_title('Module Temperature Distribution - Standard 120mm Fan')

plt.show()
'''


#for reference: Fan speed with Noctua: 6.1m/s, Qualtek: 3.8m/s through the opening of the UT363 BT airflow sensor (30mm diameter circle)
#									   0.311A @ 12V	    0.166A @12V

# This section will hopefully create a better heat map
cell_temps = np.zeros((indexes.size, 6, 8))

#fill the cell temps
for index in indexes:
	for width in np.arange(0, 4):
		for length in np.arange(0, 3):
			cell_temps[index][length][width] = data[f'{width+1}{length+1}TP'][index]
			cell_temps[index][5-length][width] = data[f'{width+1}{length+1}TP'][index]
	for width in np.arange(4, 8):
		for length in np.arange(0, 3):
			cell_temps[index][length][width] = data[f'{width+1}{length+1}TN'][index]
			cell_temps[index][5-length][width] = data[f'{width+1}{length+1}TN'][index]
			
#the array should now be filled with our values.
print(cell_temps[2200])


air_temps = np.zeros((indexes.size, 9))

for index in indexes:
	for loc in np.arange(0, 9):
		air_temps[index][loc] = data[f'MODULE_AIR_T{loc+1}'][index]

print(air_temps[2200])

fig, ax = plt.subplots()

im = ax.imshow(cell_temps[2200], interpolation='hermite', cmap='jet')
cbar = fig.colorbar(im)
cbar.set_label('Degrees C')
ax.set_title('Module Temperature Distribution - Standard 120mm Fan')

plt.show()

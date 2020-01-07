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

def calc_heat_rejection(airflow_m3_h, input_temp_c, output_temp_c):
	#1005 is the specific heat capacity of the air in J/KGdegC
	#1.18 is the density of air in Kg/m3
	heat_w = airflow_m3_h * 1005 * 1.18 * (output_temp_c - input_temp_c) / 3600
	return heat_w


def get_file():
	return askopenfile(mode = 'r', filetypes = [('CSV Files', '*.csv')], title = 'Choose your data file to plot')
filename = get_file().name
root.destroy()

user_input = eval(input("Which graph do you want to show?\n1 = Temperature Rise\n2 = Heatmap\n3 = Top Bottom Temp Difference\n4 = Heat Rejection\n"))
title_input = input("What is the title of the graph?\n")


#https://janakiev.com/blog/csv-in-python/
#https://www.dataquest.io/blog/numpy-tutorial-python/
data = np.genfromtxt(filename, delimiter=',', dtype = 'float', names=True, skip_header=1)

#number of data points
indexes = np.arange(0, data['AUX_0'].size)

if(user_input == 1):
	# This section plots a graph of different temperatures on the same axes.

	#see validating names section of this page: '-' gets removed: https://numpy.org/devdocs/user/basics.io.genfromtxt.html
	# Plot the data
	fig, ax = plt.subplots()
	
	temp_rise_rates = np.array([])
	
	data_names = np.array([])
	end_char = " "
	for i1 in range(1,9):
		for i2 in range(1,4):
			string = ""
			if (i1 < 5):
				end_char = "P"
			else:
				end_char = "N"
				
			string = (f"{str(i1)}{str(i2)}T{end_char}")
			if(i1 == 1 and i2 == 1 or i1 == 4 and i2 == 3):
				pass
			else:
				data_names = np.append(data_names, string)
			#do the averaging calculation here
			temp_rise_rate = ((data[string][2450] - data[string][2500]) / (2450-2500))
			temp_rise_rates = np.append(temp_rise_rates, temp_rise_rate)
	
	print (np.average(temp_rise_rates))
	
	for data_name in data_names:
		ax.plot(indexes, data[data_name], 'g-')
	
	ax.plot(indexes, data['43TP'], 'b-', label = 'Interior Cell')
	ax.plot(indexes, data['11TP'], 'r-', label = 'Corner Cell')
	
	plt.legend(loc = 'best')
	plt.xlabel('Time (s)')
	plt.ylabel('Temperature (C)')
	title = 'Module Temperature Rise ' + title_input
	plt.title(title)
	plt.grid()


elif(user_input == 2):
	# This section will hopefully create a better heat map
	cell_temps = np.zeros((indexes.size, 6, 8))

	max_temp_index = 0
	max_temp = 0

	#fill the cell temps
	for index in indexes:
		for width in np.arange(0, 4):
			for length in np.arange(0, 3):
				cell_temps[index][length][width] = data[f'{width+1}{length+1}TP'][index]
				cell_temps[index][5-length][width] = data[f'{width+1}{length+1}TP'][index]
				if(cell_temps[index][length][width] > max_temp):
					max_temp = cell_temps[index][length][width]
					max_temp_index = index
		for width in np.arange(4, 8):
			for length in np.arange(0, 3):
				cell_temps[index][length][width] = data[f'{width+1}{length+1}TN'][index]
				cell_temps[index][5-length][width] = data[f'{width+1}{length+1}TN'][index]
				if(cell_temps[index][length][width] > max_temp):
					max_temp = cell_temps[index][length][width]
					max_temp_index = index
				
	#the array should now be filled with our values.
	print(cell_temps[max_temp_index])

	air_temps = np.zeros((indexes.size, 9))

	for index in indexes:
		for loc in np.arange(0, 9):
			air_temps[index][loc] = data[f'MODULE_AIR_T{loc+1}'][index]

	print(air_temps[max_temp_index])

	fig, ax = plt.subplots()

	im = ax.imshow(cell_temps[max_temp_index], interpolation='hermite', cmap='jet')
	cbar = fig.colorbar(im)
	cbar.set_label('Degrees C')
	title = 'Module Temperature Distribution ' + title_input
	ax.set_title(title)


elif(user_input == 3):
	# This section will hopefully create a better heat map
	cell_temps = np.zeros((indexes.size, 3, 8))
	cell_temps_bottom = np.zeros((indexes.size, 3, 8))

	cell_temp_diff = np.zeros((3,8))

	max_temp_index = 0
	max_temp = 0

	#fill the cell temps
	for index in indexes:
		for width in np.arange(0, 4):
			for length in np.arange(0, 3):
				cell_temps[index][length][width] = data[f'{width+1}{length+1}TP'][index]
				cell_temps_bottom[index][length][width] = data[f'{width+1}{length+1}BN'][index]
				if(cell_temps[index][length][width] > max_temp):
					max_temp = cell_temps[index][length][width]
					max_temp_index = index
		for width in np.arange(4, 8):
			for length in np.arange(0, 3):
				cell_temps[index][length][width] = data[f'{width+1}{length+1}TN'][index]
				cell_temps_bottom[index][length][width] = data[f'{width+1}{length+1}BP'][index]
				if(cell_temps[index][length][width] > max_temp):
					max_temp = cell_temps[index][length][width]
					max_temp_index = index

	cell_temp_diff = np.subtract(cell_temps[max_temp_index], cell_temps_bottom[max_temp_index])
	
	cell_temp_diffs = np.array([])
	for i1 in np.arange(0,3):
		for i2 in np.arange(0,8):
			cell_temp_diffs = np.append(cell_temp_diffs, cell_temp_diff[i1][i2])
	
	temp_indexes = np.arange(0,cell_temp_diffs.size,1)

	#air temperatures
	air_temps = np.zeros((indexes.size, 9))
	for index in indexes:
		for loc in np.arange(0, 9):
			air_temps[index][loc] = data[f'MODULE_AIR_T{loc+1}'][index]
	print(air_temps[max_temp_index])

	fig, ax = plt.subplots()

	ax.plot(temp_indexes, cell_temp_diffs, 'bo')
	title = 'Temp Difference Top Bottom ' + title_input
	ax.set_title(title)

elif(user_input == 4):
	#heat rejection graph
	#average cell temperature vs amount of heat removed from the module
	air_speed_m_s = eval(input("Enter Airflow in m/s \n"))
	air_duct_diameter_mm = 30
	air_flow_m3_h = ((air_duct_diameter_mm / 2)**2 * math.pi) * air_speed_m_s / 1000 / 1000 * 3600
	
	cell_temps = np.zeros((indexes.size, 3, 8))
	cell_temps_bottom = np.zeros((indexes.size, 3, 8))
	cell_temp_average = np.array([])
	heat_rejection = np.array([])
	
	#fill the cell temps
	for index in indexes:
		num_cells = 0
		average_temp = 0
		
		for width in np.arange(0, 4):
			for length in np.arange(0, 3):
				cell_temps[index][length][width] = data[f'{width+1}{length+1}TP'][index]
				cell_temps_bottom[index][length][width] = data[f'{width+1}{length+1}BN'][index]
				num_cells += 2
				average_temp += cell_temps[index][length][width]
				average_temp += cell_temps_bottom[index][length][width]
		for width in np.arange(4, 8):
			for length in np.arange(0, 3):
				cell_temps[index][length][width] = data[f'{width+1}{length+1}TN'][index]
				cell_temps_bottom[index][length][width] = data[f'{width+1}{length+1}BP'][index]
				num_cells += 2
				average_temp += cell_temps[index][length][width]
				average_temp += cell_temps_bottom[index][length][width]
		
		average_temp /= num_cells
		cell_temp_average = np.append(cell_temp_average, average_temp)
		
		heat_w = calc_heat_rejection(air_flow_m3_h, data['EXT_TEMP_1'][index], data['EXT_TEMP_2'][index])
		heat_rejection = np.append(heat_rejection, heat_w)

	fig, ax = plt.subplots()

	ax.plot(cell_temp_average, heat_rejection, 'b-')
	title = 'Module Heat Rejection ' + title_input
	ax.set_title(title + ' at ' + str(air_flow_m3_h) + ' m3/h')
	
	
plt.grid()
plt.savefig(title)
plt.show()
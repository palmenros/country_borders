import csv
import math
import random
import json

import matplotlib.pyplot as plt
import numpy as np


def generatePolygon(ctrX, ctrY, aveRadius, irregularity, spikeyness, numVerts):
    irregularity = clip(irregularity, 0, 1) * 2 * math.pi / numVerts
    spikeyness = clip(spikeyness, 0, 1) * aveRadius

    # generate n angle steps
    angleSteps = []
    lower = (2 * math.pi / numVerts) - irregularity
    upper = (2 * math.pi / numVerts) + irregularity
    sum = 0
    for i in range(numVerts):
        tmp = random.uniform(lower, upper)
        angleSteps.append(tmp)
        sum = sum + tmp

    # normalize the steps so that point 0 and point n+1 are the same
    k = sum / (2 * math.pi)
    for i in range(numVerts):
        angleSteps[i] = angleSteps[i] / k

    # now generate the points
    x_list = []
    y_list = []
    angle = random.uniform(0, 2 * math.pi)
    for i in range(numVerts):
        r_i = clip(random.uniform(aveRadius - spikeyness, aveRadius + spikeyness), 0, 2 * aveRadius)
        x = ctrX + r_i * math.cos(angle)
        y = ctrY + r_i * math.sin(angle)

        x_list.append(x)
        y_list.append(y)

        angle = angle + angleSteps[i]
    return x_list, y_list


def clip(x, min, max):
    if min > max:
        return x
    elif x < min:
        return min
    elif x > max:
        return max
    else:
        return x


def plot_polygon(x_list, y_list):
    x_list.append(x_list[0])
    y_list.append(y_list[0])

    x = np.array(x_list)
    y = np.array(y_list)
    plt.plot(x, y)


def plot_csv(filename):
    x_list = []
    y_list = []

    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=',', quotechar='|')
        for row in reader:
            x_list.append(float(row[0]))
            y_list.append(float(row[1]))

    plot_polygon(x_list, y_list)


def generate_spain_data(filename):
	with open(filename, 'w') as outputFile:
		with open('0.geojson', encoding = 'utf-8') as jsonFile:
		    info = json.load(jsonFile)['features']
		    for feature in info:
		        if feature['properties']['ADMIN'] == 'Spain':
		            coords = feature['geometry']['coordinates']
		            outputFile.write(f'{len(coords)}\n')
		            for c in coords:
		                patch = np.array(c[0])
		                outputFile.write(f'{len(patch)}\n')

		                for x,y in patch:
		                    outputFile.write(f'{x},{y}\n')

		                #xs = list(patch[:, 0])
		                #ys = list(patch[:, 1])

		                #plt.plot(xs, ys)
		                #plt.show()
		                
		                
#filename = r'/home/pedro/dev/CLionProjects/frontieres/spain_polygon.csv'
#plot_csv(filename)
#plt.plot(0, 0, 'ro')
#plt.show()

generate_spain_data(r'/home/pedro/dev/CLionProjects/frontieres/spain_country_data.data')

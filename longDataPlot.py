import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

time = []
frontRightPot = []
backRightPot = []
steeringPot = []
Fx = []
Fy = []
Fz = []
Mx = []
My = []
Mz = []

data = [time, frontRightPot, backRightPot, steeringPot, Fx, Fy, Fz, Mx, My, Mz]
head = []

fileName = "output.csv"
MIN_TIME = 0
MAX_TIME = 6000
runNum = 0


with open(fileName, "r") as f:
	lines = f.readlines()

time_el = (int(lines[len(lines)-1].split(";")[0]) - int(lines[1].split(";")[0]))//1000000
min_capture_time = int(lines[1].split(";")[0])

print("Reading data from file... ")

for j in range(0, len(lines), 1):
	line = lines[j].split(";")
	if line[0] != "Time":
		if ((min_capture_time+(MIN_TIME*1000000)) < int(line[0]) < (min_capture_time+(MAX_TIME*1000000))):
			for i in range(len(data)):
				if i == 0:
					data[i].append((int(line[i])-min_capture_time)/1000000)
				else:
					data[i].append(int(line[i]))
	else:
		for i in range(len(data)):
			head.append(line[i])


print("\tFile reading finished with {0} rows of data collected.".format(len(data[0])))

SMALL_SIZE = 5
MEDIUM_SIZE = 10
BIGGER_SIZE = 16
colors = ("red", "green", "blue")
names = ("Pots", "Forces", "Moments")
maxs = [0, 0, 0]
mins = [1023, 1023, 1023]
plt.rc('font', size=SMALL_SIZE)          # controls default text sizes
plt.rc('axes', titlesize=BIGGER_SIZE)     # fontsize of the axes title
plt.rc('axes', labelsize=MEDIUM_SIZE)    # fontsize of the x and y labels
plt.rc('xtick', labelsize=MEDIUM_SIZE)    # fontsize of the tick labels
plt.rc('ytick', labelsize=MEDIUM_SIZE)    # fontsize of the tick labels
plt.rc('legend', fontsize=SMALL_SIZE)    # legend fontsize
plt.rc('figure', titlesize=BIGGER_SIZE)


plt.figure(num=None, figsize=(20, 6), dpi=100, facecolor='w', edgecolor='k')
print("Creating figures...")
for x in range(3):
    for i in range(3 * x + 1, 3 * x + 4):
        idata = [int(x) for x in data[i]]
        if(min(idata) < mins[x]):
            mins[x] = min(idata)
        if(max(idata) > maxs[x]):
            maxs[x] = max(idata)
        


for x in range(3):
    linesL = []

    plt.clf()
    print("\t -creating figure for Time vs {0}".format(names[x]))
    for i in range(3 * x + 1, 3 * x + 4):

        area = 1
        idata = [int(x) for x in data[i]]
        plt.yticks(np.arange(mins[x], maxs[x] + 1, max(int((maxs[x] - mins[x]) / 10), 1)))

        plt.scatter(data[0], data[i], c=colors[i%3], s=area, alpha=0.9, label=head[i])
        plt.title("{0} by Time".format(names[x]))
        plt.ylabel("Reading (ohms)")
        plt.xlabel("Time (seconds)")
        plt.savefig("{0}_{1}.png".format(runNum, names[x]))

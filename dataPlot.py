import matplotlib
import matplotlib.pyplot as plt
import numpy as np
fileName = "output.csv"
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
f_in = open(fileName, "r")
head = []
MIN_TIME = 0
MAX_TIME = 600

with open(fileName, "r") as f:
	lines = f.readlines()
for j in range(0, len(lines), 1):
    line = lines[j].split(";")
    try:
        
        if line[0] != "Time":
            if ( MIN_TIME*1000000 < (int(line[0]) - 483696) < MAX_TIME*1000000):
                for i in range(len(data)):
                    if i == 0:
                        data[i].append((int(line[i])-483696)/1000000)
                    else:
                        data[i].append(int(line[i]))
        else:
            for i in range(len(data)):
                head.append(line[i])
    except:
        pass

print(len(data[0]))

SMALL_SIZE = 5
MEDIUM_SIZE = 10
BIGGER_SIZE = 16
colors = ("red", "green", "blue")
names = ("Pots", "Forces", "Moments")
maxs = [0, 0, 0]
mins = [1023, 1023, 1023]
areas = [1, 25, 5]
plt.rc('font', size=SMALL_SIZE)          # controls default text sizes
plt.rc('axes', titlesize=BIGGER_SIZE)     # fontsize of the axes title
plt.rc('axes', labelsize=MEDIUM_SIZE)    # fontsize of the x and y labels
plt.rc('xtick', labelsize=MEDIUM_SIZE)    # fontsize of the tick labels
plt.rc('ytick', labelsize=MEDIUM_SIZE)    # fontsize of the tick labels
plt.rc('legend', fontsize=SMALL_SIZE)    # legend fontsize
plt.rc('figure', titlesize=BIGGER_SIZE) 
plt.figure(num=None, figsize=(8, 6), dpi=300, facecolor='w', edgecolor='k')

for x in range(3):
    for i in range(3 * x + 1, 3 * x + 4):
        idata = [int(x) for x in data[i]]
        if(min(idata) < mins[x]):
            mins[x] = min(idata)
        if(max(idata) > maxs[x]):
            maxs[x] = max(idata)

for x in range(3):
    plt.clf()
    for i in range(3 * x + 1, 3 * x + 4):
        idata = [int(x) for x in data[i]]
        plt.yticks(np.arange(mins[x], maxs[x], max(int((maxs[x] - mins[x]) / 10), 1)))
        plt.scatter(data[0], data[i], s=areas[i%3], c=colors[i%3], alpha=0.1, label=head[i])
        plt.title(names[x] + " by Time")
        plt.ylabel("Reading")
        plt.xlabel('Time (seconds)')
        plt.legend(loc='upper left')
        plt.savefig("test_" + names[x] + ".png")
        print(i, x)

from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

if len(sys.argv) < 3:
    print("Usage: python [MAX_N] <fname1> <fname2> ... <fname_n> <title>")
    sys.exit(1)

fig = plt.figure()
plt.title(sys.argv[-1])
plt.xlabel('# clusters')
plt.ylabel('Avg. epsilon')

cnt = 0
total = 0

all_ys = []
xs = []
current_n = None

start = 1
max_n = 3000
if sys.argv[1].isnumeric():
    max_n = int(sys.argv[1])
    start = 2

try:
    for fname in sys.argv[start:-1]:
        fp = open(fname, "r")

        lines = fp.read()
        lines = lines.split('\n')
        ys = []
        xs = []
        total_generated = 0
        total_generated_included = 0
        repeats = 0
        print(fname)

        for line in lines:
            if 'clusters' not in line:
                continue   

            cluster = int(line.split('|')[0].split()[0])
            eps = float(line.split('|')[1].split()[-1])
            xs.append(cluster)
            ys.append(eps)
            if len(ys) >= max_n :
                break

        plt.plot(
            xs,
            ys,
            linestyle='-',
            label=fname)
                
        fp.close()
except Exception as inst:
    print('File error')
    print(str(inst))
    sys.exit(1)

xs = []
ys = []
for i in range(1,max_n):
    xs.append(i)
    ys.append(1. / i)

plt.plot(
    xs,
    ys,
    linestyle='-',
    label='1 / K')
 

plt.legend()
plt.show()

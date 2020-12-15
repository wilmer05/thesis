from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

if len(sys.argv) < 2:
    print("Usage: python plot <fname1> <fname2> ... <fname_n>")
    sys.exit(1)

fig = plt.figure()
plt.title('Experiment: Sorting the items')
plt.xlabel('N')
plt.ylabel('Avg. Time')



cnt = 0
total = 0

all_ys = []
xs = []

try:
    for fname in sys.argv[1:]:
        fp = open(fname, "r")

        lines = fp.read()
        lines = lines.split('\n')
        ys = []

        for line in lines:
            if 'Time' not in line:
                continue

            t = line.split(':')[1].split('|')[0]
            ys.append(float(t))

        if len(xs) == 0:
            cnt = 1
            for y in ys:
                xs.append(cnt)
                cnt += 1

        plt.plot(
            xs,
            ys,
            linestyle='-',
            label=fname)
                
                #cnt += 1
                #if cnt > 10:
                #    break

        fp.close()
except Exception as inst:
    print('File error')
    print(str(inst))
    sys.exit(1)


plt.legend()
plt.show()

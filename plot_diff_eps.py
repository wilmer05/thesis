from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

if len(sys.argv) < 2:
    print("Usage: python <fname1> <fname2> ... <fname_n> <title>")
    sys.exit(1)

fig = plt.figure()
plt.title('Avg. Epsilon with Greedy Strategy')
plt.xlabel('N')
plt.ylabel('Avg. epsilon')

cnt = 0
total = 0

all_ys = []
xs = []
current_n = None

try:
    for fname in sys.argv[1:]:
        print(fname)
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
            if 'Mean eps' not in line and 'Nitems' not in line:
                continue   

            if 'Nitems' in line:
                xs.append(int(line.split('=')[1]))

            else:
                
                ys.append(float(line.split('=')[1]))

#            cluster = int(line.split('|')[0].split()[0])
#            eps = float(line.split('|')[1].split()[-1])
#            xs.append(cluster)
#            ys.append(eps)
#            if len(ys) >= max_n :
#                break

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

plt.legend()
plt.show()

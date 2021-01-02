from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

if len(sys.argv) < 3:
    print("Usage: python plot <fname1> <fname2> ... <fname_n>")
    sys.exit(1)

fig = plt.figure()
plt.title('Experiment: Approximate pareto curve. Algorithm: Highest epsilon first')
plt.xlabel('K')
plt.ylabel('Avg. epsilon')

cnt = 0
total = 0

all_ys = []
xs = []
current_n = None

try:
    for fname in sys.argv[1:]:
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


plt.legend()
plt.show()

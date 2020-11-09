from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

#if len(sys.argv) < 2:
#    print("Usage: python <program> (it reads from stdin)")
#    sys.exit(1)

fig = plt.figure()
plt.title('Experiment on the number of iterations a POS is alive ')
plt.xlabel('Index of the POSs ordered by weight')
plt.ylabel('Number of iterations alive')

cnt = 0
total = 0
xs = []
ys = []
cnt = 0
try:
    for line in sys.stdin:
        l = line.split(':')[1]
        ys = l.split()
        xs = []
        for i in range(len(ys)):
            ys[i] = int(ys[i])
            xs.append(i+1)

    plt.plot(
        xs,
        ys,
        'b+')


except Exception as inst:
    print('File error')
    print(str(inst))
    sys.exit(1)

#plt.legend()
plt.show()

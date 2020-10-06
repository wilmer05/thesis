from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

if len(sys.argv) < 2:
    print("Usage: python <program> <N> (it reads from stdin)")
    sys.exit(1)

fig = plt.figure()
plt.title('Drops for N={}'.format(sys.argv[1]))
plt.xlabel('Experiment number')

cnt = 0
total = 0
xs = []
cnt = 0
try:
    ys_total = []
    ys_drop = []
    for line in sys.stdin:
        xs.append(cnt)
        cnt += 1

        ys_total.append(float(line.split('=')[2].split()[0]))
        ys_drop.append(-float(line.split('=')[1].split()[0]))

    plt.plot(
        xs,
        ys_total,
        linestyle='-',
        label='#POS total')


    plt.plot(
        xs,
        ys_drop,
        linestyle='-',
        label='#Drops per instance')
        
except Exception as inst:
    print('File error')
    print(str(inst))
    sys.exit(1)

xs2 = []
fx2 = []
fx = []


#for i in range(0,170):
#    xs2.append(i + 1)
#    fx.append((total * binomial_coef(170, i+1 ))/ (2**170))
#plt.plot(xs2, fx, linestyle='-', label='f(x)=x')
#plt.plot(xs2, fx2,linestyle='-', label='f(x)=0.5 * x^2')
#plt.plot(xs2, fx3, linestyle='-', label='f(x)=0.25 * x^2')
#plt.plot(xs2, fx4, linestyle='-', label='f(x)=0.35542301 * x^(1.86456813)')
#plt.plot(xs2, fx5, linestyle='-', label='f(x)=with_log')
plt.legend()
plt.show()

from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

if len(sys.argv) < 2:
    print("Usage: python plot <fname1> <fname2> ... <fname_n>")
    sys.exit(1)

fig = plt.figure()
plt.title('Experiments')
plt.xlabel('N')



try:
    for fname in sys.argv[1:]:
        fp = open(fname, "r")

        lines = fp.read()
        lines = lines.split('\n')[2:-1]
        xs = []
        ys = []

        for line in lines:
            print(float(line.split('\t')[0]))
            xs.append(float(line.split('\t')[0])) 
            ys.append(float(line.split('\t')[2]))

        fp.close()
        plt.plot(
            xs,
            ys,
            linestyle='-',
            label='# POS {}'.format(fname.split('/')[1]))
except:
    print('File error')
    sys.exit(1)

xs2 = []
fx2 = []
fx3 = []
fx4 = []
fx5 = []
fx = []
for i in range(0,800):
    xs2.append(i + 1)
    fx.append(i+1)
    fx2.append(0.5*float(i+1)**2)
    fx3.append(0.25*float(i+1)**2)
    fx4.append(0.35542301*float(i+1)**1.86456813)
    fx5.append(0.00459851*float(i+1)*log(float(i+1))**5.32407758)

plt.plot(xs2, fx, linestyle='-', label='f(x)=x')
plt.plot(xs2, fx2,linestyle='-', label='f(x)=0.5 * x^2')
plt.plot(xs2, fx3, linestyle='-', label='f(x)=0.25 * x^2')
plt.plot(xs2, fx4, linestyle='-', label='f(x)=0.35542301 * x^(1.86456813)')
plt.plot(xs2, fx5, linestyle='-', label='f(x)=with_log')
plt.legend()
plt.show()

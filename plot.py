from matplotlib import pyplot as plt
import sys
import numpy as np

if len(sys.argv) != 2:
    print("Usage: python plot <fname>")
    sys.exit(1)

fname = sys.argv[1]
fp = open(fname, "r")

try:
    lines = fp.read()
    lines = lines.split('\n')[2:-1]
    xs = []
    ys = []
    fx2 = []
    fx3 = []
    fx = []

    for line in lines:
        print(float(line.split('\t')[0]))
        xs.append(float(line.split('\t')[0])) 
        ys.append(float(line.split('\t')[2]))
        fx.append(float(line.split('\t')[0]))
        fx2.append(0.5*float(line.split('\t')[0])**2)
        fx3.append(0.25*float(line.split('\t')[0])**2)
except:
    print('File error')
    sys.exit(1)


fig = plt.figure()
plt.title('Experiment {}'.format(fname.split('/')[1]))
plt.xlabel('N')
plt.plot(xs, ys, color='blue', linestyle='-',  label='# Pareto optimal solutions')
plt.plot(xs, fx, color='green', linestyle='-', label='f(x)=x')
plt.plot(xs, fx2, color='red', linestyle='-', label='f(x)=0.5 * x^2')
plt.plot(xs, fx3, color='yellow', linestyle='-', label='f(x)=0.25 * x^2')
plt.legend()
plt.show()

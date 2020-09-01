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



cnt = 0
total = 0
try:
    for fname in sys.argv[1:]:
        fp = open(fname, "r")

        lines = fp.read()
        lines = lines.split('\n')
        ys = []
        ys_avg = []

        for line in lines:
            print(line)
            xs = [x for x in range(0, 1001)]
            if(len(line) <= 4):
                continue
            ys = line.split(' ')
            for x in range(0, len(ys)):
                #print(ys[x])
                try:
                    ys[x] = float(ys[x])
                except:
                    ys[x] = 0

            cnt += 1
        
            xs = xs[:len(ys)]

            plt.plot(
                xs,
                ys,
                linestyle='-',
                label='#POS_ags reps: {}, n={}'.format(str(cnt), len(ys_avg)))
                
                #cnt += 1
                #if cnt > 10:
                #    break

        fp.close()
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
#plt.legend()
plt.show()

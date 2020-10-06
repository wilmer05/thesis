from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

#if len(sys.argv) < 2:
#    print("Usage: python <program> (it reads from stdin)")
#    sys.exit(1)

fig = plt.figure()
plt.title('Max weight and profits ')
plt.xlabel('N')

cnt = 0
total = 0
xs = []
cnt = 0
try:
    ys_total = []
    ys_max_weight_diff_mean = []
    ys_max_profit_diff_mean = []
    ys_max_weight_mean = []
    ys_max_profit_mean = []
    ys_division = []

    N = 0
    sum_total = 0
    sum_drop = 0
    for line in sys.stdin:
        if 'Means' in line:
            N = int(line.split('=')[1].split()[0])
            max_weight_diff = float(line.split('=')[2].split()[0])
            max_profit_diff = float(line.split('=')[3].split()[0])
            max_weight = float(line.split('=')[4].split()[0])
            max_profit = float(line.split('=')[5].split()[0])

            ys_max_weight_diff_mean.append(max_weight_diff)
            ys_max_profit_diff_mean.append(max_profit_diff)
            ys_max_weight_mean.append(max_weight)
            ys_max_profit_mean.append(max_profit)
            ys_division.append(max_weight / max_weight_diff)

            xs.append(N)

            ys_total.append(sum_total / cnt)
            sum_total = 0
            sum_drop = 0
            cnt = 0
            continue

        sum_total += (float(line.split('=')[2].split()[0]))
        cnt += 1

#    plt.plot(
#        xs,
#        ys_total,
#        linestyle='-',
#        label='Avg. #POS total')


#    plt.plot(
#        xs,
#        ys_max_weight_diff_mean,
#        linestyle='-',
#        label='Avg. max weight diff')
#
#
#    plt.plot(
#        xs,
#        ys_max_profit_diff_mean,
#        linestyle='-',
#        label='Avg. max profit diff')

    plt.plot(
        xs,
        ys_max_weight_mean,
        linestyle='-',
        label='Avg. max weight')


    plt.plot(
        xs,
        ys_max_profit_mean,
        linestyle='-',
        label='Avg. max profit')




#    plt.plot(
#        xs,
#        ys_division,
#        linestyle='-',
#        label='Avg. Max weight / Avg. Max weight diff')

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

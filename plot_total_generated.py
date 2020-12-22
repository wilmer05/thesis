from matplotlib import pyplot as plt
import sys
import numpy as np
from math import log

if len(sys.argv) < 3:
    print("Usage: python plot <fname1> <fname2> ... <fname_n>")
    sys.exit(1)

print_included = sys.argv[1] == '--with-included'

fig = plt.figure()
plt.title('Experiment: Sorting the items')
plt.xlabel('N')
ylabel = 'Avg. solutions on the pareto Curve'
if print_included:
    ylabel = 'Avg. total generated with eliminated solutions'
plt.ylabel(ylabel)



cnt = 0
total = 0

all_ys = []
xs = []
current_n = None

try:
    for fname in sys.argv[2:]:
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
            if 'Round' not in line and 'Total generated' not in line:
                continue   

            if 'Round' in line:
                if current_n != None and repeats > 0 :
                    xs.append(current_n)
                    if print_included:
                        ys.append(float(total_generated_included) / float(repeats))
                    else:
                        ys.append(float(total_generated) / float(repeats))

                current_n = int(line.split('=')[1].split(' ')[0])
                total_generated = 0
                total_generated_included = 0
                repeats = 0
                continue

            repeats += 1
            total_generated += float(line.split(',')[0].split()[-1])
            total_generated_included += float(line.split(',')[1].split()[-1])

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

import sys
import os

ws = []
ps = []
W = 0
drop_before = []

def run_instance(ws, ps, drop_before):
    total = 0
    f = open("tmp", "w")
    f.write(W + "\n")
    for w, p in zip(ws, ps):
        f.write(w + " "  + p + "\n")    

    f.close()

    cmd = "./src/run " + " ".join(sys.argv[1:3] ) + " " + str(len(ws)) + " " + str(len(ps)) + " 1  < ./tmp > ./tmp_result" 
    print(cmd)
    os.system(cmd)

    f2 = open("./tmp_result")
    lines = f2.read().split('\n')
    drop_after = 0
    cnt = 0
    for line in lines:
        if "Drop" in line:
            drop_after += int(line.split("...")[0].split(":")[1])
            cnt += 1
    if cnt > 0 :
        drop_after /= cnt
    f2.close()

    print('Drop Before: {} and After: {} and cnt: {}'.format(drop_before, drop_after, cnt))
    

for line in sys.stdin:

    if len(line) <= 1:
        continue
    
    if "Drop" in line:

        if len(ws) != 0:
            run_instance(ws, ps, drop_before)

        ws = []
        ps = []
        drop_before = line.split("...")[0].split(":")[1]
        drop_before = int(drop_before)
        continue

    else:
        sp = line.split()
        if len(sp) == 1:
            W = sp[0]
            continue

        w = sp[0] 
        p = sp[1] 
        ws.append(w)
        ps.append(p)

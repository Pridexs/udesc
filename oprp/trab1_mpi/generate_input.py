import sys
from random import randint

f = open('input', 'w')

if (len(sys.argv) < 2):
    print('Enter n items')
    sys.exit()

n = int(sys.argv[1])

f.write(str(n)+'\n')

for x in range(0, n):
    for y in range(0, n):
        if (y != 0):
            f.write(' ' + str(randint(0, 400)))
        else:
            f.write(str(randint(0, 400)))
    f.write('\n')

for x in range(0, n):
    if (x != 0):
        f.write(' ')
    f.write(str(randint(0,400)))

f.close()


import sys
from random import randint

f = open('input', 'w')

if (len(sys.argv) < 3):
    print('Enter bag size and number of items')
    sys.exit()

bagsize = randint(0,int(sys.argv[1]))
n = int(sys.argv[2])

f.write(str(bagsize)+'\n')
f.write(str(n)+'\n')

for x in range(0, n):
    f.write(str(randint(1,int(bagsize/3)))+' '+str(randint(1,int(bagsize/3)))+'\n')

f.close()


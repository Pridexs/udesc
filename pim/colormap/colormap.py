import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from numpy.random import randn
from PIL import Image

m=list()
fh = open("mapa.txt", "r")
for line in fh: 
    #print line,
    #print type(line)
    aux=line.split() # quebra a lisna em uma 'list' de strings
    # monta um vetor com as strings individuais lidas por linhas
    for i, val in enumerate(aux):
        b=np.fromstring(val, dtype=int, sep=' ')
        m.append(b)

M=np.asarray(m)

# converte o vetor M de 256*3 elementos em um array 256x3
M=np.reshape(M,(256,3))

print M

im = Image.open('a.png')
out = Image.new("RGB", im.size)
height,width = im.size

for i in range(0,height):
	for j in range(0, width):
		pixel = im.getpixel((i,j))[0]
		out.putpixel((i,j), (M[pixel][0], M[pixel][1], M[pixel][2]))

out.save("out.png", "PNG")
		

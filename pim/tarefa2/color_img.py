import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from numpy.random import randn
from PIL import Image

# Verificando se os argumentos foram passados
if ( len(sys.argv) != 3 ):
    print("Usage: python colormap.py <nome_imagem> <nome_color_map>")

nome_imagem = sys.argv[1]
nome_color_map = sys.argv[2]


m=list()
fh = open(nome_color_map, "r")
for line in fh:
    aux=line.split()
    for i, val in enumerate(aux):
        b=np.fromstring(val, dtype=int, sep=' ')
        m.append(b)

M=np.asarray(m)

# converte o vetor M de 256*3 elementos em um array 256x3
M=np.reshape(M,(256,3))

# Caso queira usar um mapa de cores do python, usar isso.
# M = plt.cm.get_cmap('Vega20c')

# im = Image.open('mapaEUA.jpg')
im = Image.open(nome_imagem).convert("L")

out = Image.new("RGB", im.size)
height,width = im.size

for i in range(0,height):
    for j in range(0, width):
        pixel = M[im.getpixel((i,j))]
        out.putpixel((i,j),  (np.uint8(pixel[0]), np.uint8(pixel[1]), np.uint8(pixel[2]) ))

out.save("out.jpeg", "JPEG")

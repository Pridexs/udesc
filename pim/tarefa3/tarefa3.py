# Sobel edge detector with local maximum calculation
# Code is very messy was just trying to understand the concept

import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from numpy.random import randn
from PIL import Image
import math

np.set_printoptions(threshold=np.nan)

# Median Filter
# Its wrapping up borders, not extending them
def medianFilter(img):
    width, height = img.size
    window_height = 3
    window_width = 3
    window = np.zeros(3*3)
    newImg = Image.new("L", img.size)

    edgex = int(window_width / 2)
    edgey = int(window_height / 2)

    for x in range(0, width):
        for y in range(0, height):
            i = 0
            for fx in range(0, window_width):
                for fy in range(0, window_height):
                    nx = x + fx - edgex
                    ny = y + fy - edgey 

                    if ( nx < 0 ):
                        nx = window_width - nx
                    elif (nx >= window_width):
                        nx = nx - window_width

                    if ( ny < 0 ):
                        ny = window_height - ny
                    elif (ny >= window_height):
                        ny = ny - window_height

                    window[i] = img.getpixel( (nx, ny) )
                    i = i + 1
            window = np.sort(window)
            middle_value = np.uint8(window[ int((window_width * window_height) / 2) ])
            newImg.putpixel((x,y), int(middle_value))

    return newImg

def pontosSemInterpolacao(S, i, j, angulo):
    ponto1 = 0
    ponto2 = 0

    if (angulo > (np.pi / 6.0) and angulo < (np.pi / 3.0)):
        ponto1 = S[i+1][j+1]
        ponto2 = S[i-1][j-1]
    elif (angulo >= (np.pi / 3.0) and angulo < ((2.0 * np.pi)/3)):
        ponto1 = S[i+1][j]
        ponto2 = S[i-1][j]
    elif (angulo >= ((2.0 * np.pi)/3) and angulo < ((5.0 * np.pi) / 6.0)):
        ponto1 = S[i-1][j-1]
        ponto2 = S[i-1][j+1]
    else:
        ponto1 = S[i][j+1]
        ponto2 = S[i][j-1]

    if (S[i][j] >= ponto1 and S[i][j] >= ponto2):
        return S[i][j]
    else:
        return 0

def pontosComInterpolacao(S, i, j, angulo):
    b = (np.pi / 4.0)
    a = 0
    p1 = 0
    p2 = 0
    p3 = 0
    p4 = 0

    if (angulo >= 0.0 and angulo <= (np.pi / 4.0)):
        a = angulo
        p1 = S[i+1][j+1]
        p2 = S[i][j+1]
        p3 = S[i-1][j-1]
        p4 = S[i][j-1]
    elif (angulo <= (np.pi / 2.0)):
        a = angulo - (np.pi / 4.0)
        p1 = S[i+1][j]
        p2 = S[i+1][j+1]
        p3 = S[i-1][j]
        p4 = S[i-1][j-1]
    elif (angulo <= ((3.0 * np.pi) / 4.0)):
        a = angulo - (np.pi / 2.0)
        p1 = S[i-1][j-1]
        p2 = S[i-1][j]
        p3 = S[i+1][j+1]
        p4 = S[i][j+1]
    else:
        a = angulo - ((np.pi * 3.0) / 4.0)
        p1 = S[i-1][j]
        p2 = S[i-1][j-1]
        p3 = S[i][j+1]
        p4 = S[i+1][j+1]

    temp = angulo / b
    ponto1 = temp * p1 + (1 - temp) * p2
    ponto2 = temp * p3 + (1 - temp) * p4

    if (S[i][j] >= ponto1 and S[i][j] >= ponto2):
        return S[i][j]
    else:
        return 0

def gradMaximosLocais(S, G_x, G_y, img, interp=False):
    newImg = Image.new(img.mode, img.size)
    D = np.zeros(G_x.shape).astype('float64')
    for i in range(G_x.shape[0]):
        for j in range(G_x.shape[1]):
                D[i][j] = np.arctan2( np.float(G_y[i][j]), np.float(G_x[i][j]) )
                if (D[i][j] < 0):
                    D[i][j] = D[i][j] + np.pi

    window_height = 3
    window_width = 3
    edgex = int(window_width / 2)
    edgey = int(window_height / 2)
    for i in range(0+edgey, height-edgey):
        for j in range(0+edgex, width-edgex):
            angulo = S[i][j]
           
            if (not interp):
                newImg.putpixel( (j,i), int(pontosSemInterpolacao(S, i, j, angulo)))
            else:
                newImg.putpixel( (j,i), int(pontosComInterpolacao(S, i, j, angulo)))

    return newImg 

# Verificando se os argumentos foram passados
if ( len(sys.argv) != 2 ):
    print("Usage: python colormap.py <nome_imagem>")

nome_imagem = sys.argv[1]

# Abrindo imagem e convertendo pra B&W de uma vez
img = Image.open(nome_imagem).convert("L")
width, height = img.size

# Imagem com o filtro de mediana aplicado
img_median = medianFilter(img)

# se quiser aplicar sobre filtro da mediana, descomente essa linha
img = img_median

arr = np.array(img)
G_y, G_x = np.gradient(arr.astype('float64'))

# S eh a matriz de magnitude
S = np.zeros(G_x.shape)
for i in range(G_x.shape[0]):
    for j in range(G_x.shape[1]):
        S[i][j] = int( math.sqrt(math.pow(G_x[i][j], 2) + math.pow(G_y[i][j], 2)) )

newImg = Image.new("L", img.size)
print(G_x.shape, img.size)
for i in range(G_x.shape[1]):
    for j in range(G_x.shape[0]):
        newImg.putpixel( (i,j), int(S[j][i]) )

newImg.save("out_magnitude.jpg", "JPEG")

gradMaximosLocais(S, G_x, G_y, img, interp=True).save("edges.jpg", "JPEG")

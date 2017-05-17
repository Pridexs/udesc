# Sobel edge detector with local maximum calculation
# Code is very messy, was just trying to understand the concept
# Not optimized at allllll
# Do not use thiss for serious stuffff

import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from numpy.random import randn
from PIL import Image
import math

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
                        nx = width + nx
                    elif (nx >= width):
                        nx = nx - width

                    if ( ny < 0 ):
                        ny = height + ny
                    elif (ny >= height):
                        ny = ny - height

                    window[i] = img.getpixel( (nx, ny) )
                    i = i + 1
            window = np.sort(window)
            middle_value = np.uint8(window[ int((window_width * window_height) / 2) ])
            newImg.putpixel((x,y), int(middle_value))

    return newImg


def blurImg(img):
    width, height = img.size
    window_height = 5
    window_width = 5

    newImg = Image.new("L", img.size)

    edgex = 2
    edgey = 2

    for x in range(0, width):
        for y in range(0, height):
            value = 0.0
            for fx in range(0, window_width):
                for fy in range(0, window_height):
                    nx = x + fx - edgex
                    ny = y + fy - edgey 

                    if ( nx < 0 ):
                        nx = width + nx
                    elif (nx >= width):
                        nx = nx - width

                    if ( ny < 0 ):
                        ny = height + ny
                    elif (ny >= height):
                        ny = ny - height

                    # print(width, height, nx, ny)
                    pixel = img.getpixel( (nx, ny) )
                    value = value + pixel

            value = np.clip( value / 25.0, 0, 255)
            newImg.putpixel((x,y), int(value))

    return newImg


def highBoost(img, constant):
    width, height = img.size

    newImg = Image.new("L", img.size)
    mask = Image.new("L", img.size)

    blurredImg = blurImg(img)

    d1 = np.array(img).astype("float64")
    d2 = np.array(blurredImg).astype("float64")
    d3 = np.zeros(d1.shape).astype("float64")

    for x in range(0, width):
        for y in range(0, height):
            d3[y][x] = float(d1[y][x] - d2[y][x])

    for x in range(0, width):
        for y in range(0, height):
            value = np.clip( d1[y][x] + d3[y][x] * constant, 0, 255)
            newImg.putpixel((x,y), int(value))

    return newImg

# Wrong highBoost
# def highBoost(img, constant):
    # width, height = img.size
    # window_height = 3
    # window_width = 3

    # newImg = Image.new("L", img.size)

    # edgex = 1
    # edgey = 1

    # for x in range(0, width):
        # for y in range(0, height):
            # value = 0.0
            # for fx in range(0, window_width):
                # for fy in range(0, window_height):
                    # nx = x + fx - edgex
                    # ny = y + fy - edgey 

                    # if ( nx < 0 ):
                        # nx = width + nx
                    # elif (nx >= width):
                        # nx = nx - width

                    # if ( ny < 0 ):
                        # ny = height + ny
                    # elif (ny >= height):
                        # ny = ny - height

                    # # print(width, height, nx, ny)
                    # pixel = img.getpixel( (nx, ny) )
                    # if (nx == x and ny == y):
                        # value = value + ((constant * 9 - 1) * pixel)
                    # else:
                        # value = value - (pixel)

            # value = np.clip( value / 9.0, 0, 255)
            # newImg.putpixel((x,y), int(value))

    # return newImg

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
            angulo = np.arctan2( G_y[i][j], G_x[i][j] )
           
            if (not interp):
                newImg.putpixel( (j,i), int(pontosSemInterpolacao(S, i, j, angulo)))
            else:
                newImg.putpixel( (j,i), int(pontosComInterpolacao(S, i, j, angulo)))

    return newImg 

# Verificando se os argumentos foram passados
if ( len(sys.argv) != 3 ):
    print("Usage: python colormap.py <nome_imagem> <nome_output>")

nome_imagem = sys.argv[1]
nome_output = sys.argv[2]

# Abrindo imagem e convertendo pra B&W de uma vez
img = Image.open(nome_imagem).convert("L")
width, height = img.size

# Imagem com o filtro de mediana aplicado
# img_median = medianFilter(img)

# se quiser aplicar sobre filtro da mediana, descomente essa linha
# img = img_median

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

newImg.save(nome_output + "_edges_mag.jpg", "JPEG")
highBoost(newImg, 0.5).save(nome_output + "_mag_0.5.jpg", "JPEG")
highBoost(newImg, 1.0).save(nome_output + "_mag_1.0.jpg", "JPEG")
highBoost(newImg, 1.5).save(nome_output + "_mag_1.5.jpg", "JPEG")

gradImg = gradMaximosLocais(S, G_x, G_y, img, interp=False)
gradImg.save(nome_output + "_grad.jpg", "JPEG")
highBoost(gradImg, 0.5).save(nome_output + "_grad_0.5.jpg", "JPEG")
highBoost(gradImg, 1.0).save(nome_output + "_grad_1.0.jpg", "JPEG")
highBoost(gradImg, 1.5).save(nome_output + "_grad_1.5.jpg", "JPEG")

gradImg = gradMaximosLocais(S, G_x, G_y, img, interp=True)
gradImg.save(nome_output + "_grad_interp.jpg", "JPEG")
highBoost(gradImg, 0.5).save(nome_output + "_grad_0.5_interp.jpg", "JPEG")
highBoost(gradImg, 1.0).save(nome_output + "_grad_1.0_interp.jpg", "JPEG")
highBoost(gradImg, 1.5).save(nome_output + "_grad_1.5_interp.jpg", "JPEG")

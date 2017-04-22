# coding=utf-8

import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from numpy.random import randn
from PIL import Image

def calculateHistogram(img):
    hist = [0] * 256
    data = list(img.getdata())
    for p in data:
        hist[p] += 1
    return hist

def histogramEqualization(img, hist):
    height, width = img.size
    #quantidade de pixels da img
    size = float(height * width)
    g_f = [0] * 256

    # Normalizacao
    for i in range(0, len(hist)):
        g_f[i] = float(hist[i] / size)

    new_hist = [0] * 256
    #calcula o valor do hist na enésima posição
    new_hist[0] = int( (g_f[0] * 255) + 0.5)
    for i in range(1, len(hist)):
        g_f[i] += g_f[i-1]
        new_hist[i] = int( (g_f[i] * 255) + 0.5)

    # print("Antes de equalizar: ")
    # print(hist)
    # print("Depois de equalizar: ")
    # print(new_hist)

    return new_hist


# Inicio
if (len(sys.argv) != 2):
    sys.exit("Usage: python hist_eq.py <nome_image>")

# Abrindo imagem
img_name = sys.argv[1]
img1 = Image.open(img_name).convert("L")
height,width = img1.size

# Plottando o Histogram antes da Equalizacao
# plt.figure(figsize=(12,12))
plt.hist(np.asarray(img1).ravel(), 256,[0,256])
plt.savefig('hist_in.jpg')
plt.clf()

out = Image.new(img1.mode, (height, width))

# Obtendo o Histogram manualmente
histogram = calculateHistogram(img1)
# Equalizando o histograma
histogram_ = histogramEqualization(img1, histogram)

for i in range(0, height):
    for j in range(0, width):
        pixel = img1.getpixel((i,j))
        out.putpixel((i,j), histogram_[pixel])

out.save("img_out.jpg", "JPEG")

# Plottando o Histogram depois da Equalizacao
plt.hist(np.asarray(out).ravel(), 256, [0,256])
plt.savefig('hist_out.jpg')
plt.clf()

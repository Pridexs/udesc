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
        hist[p[0]] += 1
    return hist

def histogramEqualization(img, hist):
    height, width = img.size
    #quantidade de pixels da img
    size = float(height * width)
    g_f = [0] * 256
    #calcula ate o round(gk * num_tons_cinza)
    for i in range(0, len(hist)):
        g_f[i] = ( hist[i] * (len(hist) - 1) ) / size

    new_hist = [0] * 256
    #calcula o valor do hist na enésima posição
    for i in range(0, len(hist)):
        #new_hist[i] = somatorio ate então
        for j in range(0, i):
            new_hist[i] += int(g_f[j])

    print("Antes de equalizar: ")
    print(hist)
    print("Depois de equalizar: ")
    print(new_hist)

    return new_hist


# Inicio
if (len(sys.argv) != 2):
    sys.exit("Usage: python hist_eq.py <nome_image>")

# Abrindo imagem
img_name = sys.argv[1]
img = Image.open(img_name)

# Plottando o Histogram antes da Equalizacao
plt.hist(np.asarray(img).ravel(), 255)
plt.savefig('hist1.jpg')
plt.clf()


img1 = Image.open(img_name).convert("L")
height,width = img1.size
out = Image.new(img1.mode, (height, width))


# Obtendo o Histogram manualmente
histogram = calculateHistogram(img)
# Equalizando o histograma
histogram_ = histogramEqualization(img, histogram)

for i in range(0, height):
	for j in range(0, width):
		pixel = img1.getpixel((i,j))
		out.putpixel((i,j), histogram_[pixel])

out.save("out_teste.jpg", "JPEG")

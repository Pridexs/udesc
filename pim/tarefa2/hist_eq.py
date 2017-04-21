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
    p_f = [0] * 256
    g_k = [0] * 256
    where_to_put = [0] * 256
    accumulate_sum = 0.0
    for i in range(0, len(hist)):
        p_f[i] = hist[i]/size
        accumulate_sum += p_f[i]
        g_k[i] = accumulate_sum
        where_to_put[i] = int(g_k[i] * 255 + 0.5)

    #print(where_to_put)
    new_hist = [0] * 256
    for i in range(0, len(hist)):
        new_hist[ where_to_put[i] ] +=  hist[i]

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

# Obtendo o Histogram manualmente
histogram = calculateHistogram(img)
histogram_ = histogramEqualization(img, histogram)

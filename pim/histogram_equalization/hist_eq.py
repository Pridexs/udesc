import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from numpy.random import randn
from PIL import Image

def calculateHistogram(img):
    hist = [0] * 255
    data = list(img.getdata())
    for p in data:
        hist[p[0]] += 1
    return hist

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


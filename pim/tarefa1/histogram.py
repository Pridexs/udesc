#!/usr/bin/env python
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
from PIL import Image

img = Image.open('mapaEUA.jpg')
plt.hist(np.asarray(img).ravel(), 20)

plt.savefig('histogram_mapaEUA.jpg')

# Para limpar os dados do plot antigo
plt.clf()

img2 = Image.open('pepinos.jpg')
plt.hist(np.asarray(img2).ravel(), 255)

plt.savefig('histogram_pepinos.jpg')

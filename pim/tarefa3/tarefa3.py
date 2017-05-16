import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from numpy.random import randn
from PIL import Image

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

# Verificando se os argumentos foram passados
if ( len(sys.argv) != 2 ):
    print("Usage: python colormap.py <nome_imagem>")

nome_imagem = sys.argv[1]

# Abrindo imagem e convertendo pra B&W de uma vez
img = Image.open(nome_imagem).convert("L")
width, height = img.size


medianFilter(img).save("out.jpeg", "JPEG")


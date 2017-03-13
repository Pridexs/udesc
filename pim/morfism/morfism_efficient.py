#!/usr/bin/python3

#
# Very simple morphism/cross fading script.
#
# Alexandre Maros - 2017/1
#
# Credit for the Images: Don't Hug Me I'm Scared
#

from PIL import Image
import numpy as np

# Images should be the same size!!
img1 = Image.open('img1.jpg')
img2 = Image.open('img2.jpg')

for u in range(0,11):
    print("Generating image " + str(u) + "...")
    alpha = u / 10
    M1 = np.array(img1)
    M2 = np.array(img2)
    M3 = (1-alpha) * M1 + alpha * M2          
    
    img_morphed = Image.fromarray(np.uint8(M3))
    img_morphed.save("img_" + str(u) + '.jpg', "JPEG")

print("Done.")



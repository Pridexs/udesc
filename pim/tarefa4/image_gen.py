import scipy.misc
import numpy as np

img = np.zeros((500,500))
img[100:400, 100:400] = np.eye(300)
scipy.misc.imsave('imgs/initial_0.png', img)

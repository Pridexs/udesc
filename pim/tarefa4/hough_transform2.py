import numpy as np
import matplotlib.pyplot as plt
import cv2
from scipy import misc

def hough_line(img, angle_step=1):
  """
  Hough transform for lines

  Input:
  img - 2D binary image with nonzeros representing edges
  angle_step - Spacing between angles to use every n-th angle
    between -90 and 90 degrees. Default step is 1.

  Returns:
  accumulator - 2D array of the hough transform accumulator
  theta - array of angles used in computation, in radians.
  rhos - array of rho values. Max size is 2 times the diagonal
         distance of the input image.
  """
  # Rho and Theta ranges
  thetas = np.deg2rad(np.arange(-90.0, 90.0, angle_step))
  # img=np.mean(img, axis=2)
  width, height = img.shape
  diag_len = np.ceil(np.sqrt(width * width + height * height)).astype(int)
  rhos = np.linspace(-diag_len, diag_len, diag_len * 2.0).astype(int)

  # Cache some resuable values
  cos_t = np.cos(thetas)
  sin_t = np.sin(thetas)
  num_thetas = len(thetas)

  # Hough accumulator array of theta vs rho
  accumulator = np.zeros((2 * diag_len, num_thetas), dtype=np.uint64)
  y_idxs, x_idxs = np.nonzero(img)  # (row, col) indexes to edges

  # Vote in the hough accumulator
  for i in range(len(x_idxs)):
    x = x_idxs[i]
    y = y_idxs[i]

    for t_idx in range(num_thetas):
      # Calculate rho. diag_len is added for a positive index
      rho = int(round(x * cos_t[t_idx] + y * sin_t[t_idx]) + diag_len)
      accumulator[rho, t_idx] += 1

  return accumulator, thetas, rhos

def show_hough_line(img, accumulator):
  import matplotlib.pyplot as plt

  fig, ax = plt.subplots(1, 2, figsize=(10, 10))

  ax[0].imshow(img, cmap=plt.cm.gray)
  ax[0].set_title('Input image')
  ax[0].axis('image')

  ax[1].imshow(
    accumulator, cmap=plt.cm.gray,
    extent=[np.rad2deg(thetas[-1]), np.rad2deg(thetas[0]), rhos[-1], rhos[0]])
  ax[1].set_aspect('equal', adjustable='box')
  ax[1].set_title('Hough transform')
  ax[1].set_xlabel('Angles (degrees)')
  ax[1].set_ylabel('Distance (pixels)')
  ax[1].axis('image')

  #plt.axis('off')
  plt.savefig('imgs/output.png', bbox_inches='tight')
  plt.show()

if __name__ == '__main__':
  imgpath1 = 'imgs/hexagon_nut.jpg' 
  #imgpath2 = 'imgs/black_line2.png'
  #img = misc.imread(imgpath)
  image1 = cv2.imread(imgpath1)
  img1 = cv2.cvtColor(image1, cv2.COLOR_BGR2GRAY)
  accumulator, thetas, rhos = hough_line(img1)
  # ****************************************** #
  #image2 = cv2.imread(imgpath2)
  #img2   = cv2.cvtColor(image2, cv2.COLOR_BGR2GRAY)
  #accumulator2, thetas2, rhos2 = hough_line(img2) 
  
  plt.imshow(accumulator) #Needs to be in row,col order
  plt.savefig("imgs/output_img1.png")

  #plt.imshow(accumulator2)
  #plt.savefig("imgs/output_img2.png") 
  # accumulator.show()
  # show_hough_line(img, accumulator)


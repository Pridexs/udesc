import cv2
import numpy as np
from skimage.measure import structural_similarity as ssim
from matplotlib import pyplot as plt


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


def compare_images(imageA, imageB, title):
	# compute the mean squared error and structural similarity
	# index for the images
	s = ssim(imageA, imageB)
 
	# setup the figure
	fig = plt.figure(title)
	plt.suptitle("SSIM: %.2f" % (s))
 
	# show first image
	ax = fig.add_subplot(1, 2, 1)
	plt.imshow(imageA, cmap = plt.cm.gray)
	plt.axis("off")
 
	# show the second image
	ax = fig.add_subplot(1, 2, 2)
	plt.imshow(imageB, cmap = plt.cm.gray)
	plt.axis("off")
 
	# show the images
	plt.show()

img = cv2.imread('imgs/black_line.png',0)
img = cv2.Canny(img, 100, 200) 
img, thetas, rhos = hough_line(img)
f = np.fft.fft2(img)
fshift = np.fft.fftshift(f)
magnitude_spectrum = 20*np.log(np.abs(fshift))


img2 = cv2.imread('imgs/black_line2.png',0)
img2 = cv2.Canny(img2, 100, 200) 
img2, thetas, rhos = hough_line(img2)
f2 = np.fft.fft2(img2)
fshift2 = np.fft.fftshift(f2)
magnitude_spectrum2 = 20*np.log(np.abs(fshift2))

print("SSIM %.2f" % ssim(magnitude_spectrum, magnitude_spectrum2))

plt.subplot(121),plt.imshow(img, cmap = 'gray')
plt.title('Input Image'), plt.xticks([]), plt.yticks([])
plt.subplot(122),plt.imshow(magnitude_spectrum, cmap = 'gray')
plt.title('Espectro Correspondente'), plt.xticks([]), plt.yticks([])

plt.show()

plt.subplot(121),plt.imshow(img2, cmap = 'gray')
plt.title('Input Image 2'), plt.xticks([]), plt.yticks([])
plt.subplot(122),plt.imshow(magnitude_spectrum2, cmap = 'gray')
plt.title('Espectro Correspondente'), plt.xticks([]), plt.yticks([])

plt.show()

compare_images(np.abs(fshift), np.abs(fshift),  "Original vs. Original"  )
compare_images(np.abs(fshift), np.abs(fshift2), "Original vs Rotacionada")

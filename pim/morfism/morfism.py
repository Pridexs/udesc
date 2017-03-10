# Very simple morphism/cross shading script.
# This one is slow and only for educational purposes.
#
# Alexandre Maros - 2017/1
#
# Credit for the Images: Don't Hug Me I'm Scared
#

from PIL import Image

img1 = Image.open('img1.jpg')
img2 = Image.open('img2.jpg')

# The images should be the same size, but I am not going to add a check to see
# if they are.
width,height = img1.size

img_morphed = Image.new(img1.mode, (width, height))

for u in range(0,11):
    print("Generating image " + str(u) + "...")
    alpha = u / 10
    for i in range(0,height):
        for j in range(0,width):
            p1 = tuple([(1 - alpha) * z for z in img1.getpixel((i,j))])
            p2 = tuple([alpha * z for z in img2.getpixel((i,j))])
            p3 = ( int(p1[0]+p2[0]), int(p1[1]+p2[1]), int(p1[2]+p2[2]) )
            img_morphed.putpixel( (i,j), p3 )
            
    img_morphed.save("img_" + str(u) + '.jpg', "JPEG")

print("Done.")

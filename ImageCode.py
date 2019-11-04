# Image Conversion Program (Program 1 of Project) final: 24/09/19

from PIL import Image
import numpy

pageWidth = 20
pageHeight = 30

# creating value scale dictionary
vScale = {0: 10, 1: 9, 2: 8, 3: 7, 4: 6, 5: 5, 6: 4, 7: 3, 8: 2, 9: 1}

try:
    originalIm = Image.open("/Users/dyuti/OneDrive/School Year 12/EPQ/Code/Apple.jpg")
except:
    print("the original image could not be opened")

# converting to greyscale
greyIm = originalIm.convert("L")

# resizing image
scaleFactor = (greyIm.width)/(greyIm.height)
w = pageWidth
h = int(w*scaleFactor)

while h > pageHeight: # ensures that the picture will fit on A4 page when drawn
    w = w - 1
    h = int(w*scaleFactor)

(width, height) = (w,h)
newIm = greyIm.resize((width, height))


# creating dot density array
dotDen = numpy.empty([h,w])
x = 0
c = 0

# categorizing the pixel values based on value scale
for x in range(0,w):
    y=0
    for y in range(0,h):
        c = newIm.getpixel((x,y))
        key = int(c/26)
        code = vScale[key]
        dotDen[y,x] = code

# save dotDen array as TXT (in same directory as image)
numpy.savetxt("/Users/dyuti/OneDrive/School Year 12/EPQ/Code/picCode.TXT",dotDen, delimiter=',', fmt='%d')

# save dotDen dimensions as TXT for Arduino program
size_F = open("/Users/dyuti/OneDrive/School Year 12/EPQ/Code/size.TXT","w+")

h2 = str(h)
w2 = str(w)

size_F.write(h2)
size_F.write("\r\n")
size_F.write(w2)
size_F.close()
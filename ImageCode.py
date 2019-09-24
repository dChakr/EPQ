# Image Conversion Program (Program 1 of Project) final: 24/09/19

from PIL import Image
import numpy

pageWidth = 20
pageHeight = 30

# creating value scale dictionary
vScale = {0: 10, 1: 9, 2: 8, 3: 7, 4: 6, 5: 5, 6: 4, 7: 3, 8: 2, 9: 1}

try:
    originalIm = Image.open("/Users/Apple.jpg") #my specific file path omitted for privacy
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

# save dotDen array as csv (in same directory as image)
numpy.savetxt("/Users/picCode.TXT",dotDen, delimiter=',', fmt= '%d') #my specific file path omitted for privacy


try:
    from PIL import Image
except ImportError:
    import Image 

import pytesseract
import matplotlib.pyplot as plt 
import numpy as np
import os
import cv2 as cv 


# clear command line
clear = lambda:os.system('cls')

imgname = [None] * 100
for i in range(1, 100):
    imgname[i] = "char%05d.pbm" % (i)

dirpath = 'Chars_data/BWChars'
plt.figure()

for j in range(1, 100):
    address = os.path.join(dirpath, imgname[j])
    print("address is ", address)
    # read the char in this image
    try:
        image_cv = cv.imread(address)
        image_rgb = cv.cvtColor(image_cv, cv.COLOR_BGR2RGB)
    except IOError:
        print("Error: Cannot open the image file!")
        exit(1)

    result = pytesseract.image_to_string(image_rgb, lang='chi_tra')
    print("=> character is ", result)

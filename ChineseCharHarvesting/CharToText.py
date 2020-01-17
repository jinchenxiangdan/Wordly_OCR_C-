
try:
    from PIL import Image
except ImportError:
    import Image 

import pytesseract
import matplotlib.pyplot as plt 
import numpy as np
import os

print("=====")
print(pytesseract.image_to_string(
    Image.open("/home/wan/Desktop/ShawnJin_Workspace/Images/text.png.jpeg")))
print("=====")
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
        image = Image.open(address)
    except IOError:
        print("Error: Cannot open the image file!")
        exit(1)

    result = pytesseract.image_to_string(image, lang='chi_tra')
    print("=> character is ", result)

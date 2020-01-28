# MATLAB test running time: self time: 38.491s , total tiem 64.412s 
# ANCHOR Shawn Jin
# 
try:
    from PIL import Image
except ImportError:
    import Image 

import pytesseract
import matplotlib.pyplot as plt 
import numpy as np
import os
from cv2 import cv2 as cv 
import matlab.engine
from oct2py import Oct2Py


#---------------------------------------------------#
# functions                                         #
#---------------------------------------------------#

# returns the relative path according to the file name
# dir_path is 'Chars_data/BWChars'
def getBWCharsPath(file_name):
    dirpath = 'Chars_data/BWChars'
    return os.path.join(dirpath, file_name)

def drawTable(data):
    f = plt.gcf()
    plt.subplot(2,1,1)
    

#---------------------------------------------------#
# end of function part                              #
#---------------------------------------------------#



# clear command line
clear = lambda:os.system('cls')

imgname = [None] * 100
# for i in range(1, 100):


# open a figure window
plt.figure()

# check the first 100 images 
mat_eng = matlab.engine.start_matlab()
for j in range(1, 100):

    address = getBWCharsPath("char%05d.pbm" % (j))
    print("address is ", address)
    # read the char in this image
    try:
        # image_cv = cv.imread(address)
        image_matlab = mat_eng.imread(address)
    except IOError:
        print("Error: Cannot open the image file!")
        exit(1)
    # get result of OCR
    result = mat_eng.ocr_matlab(image_matlab)
    if len(result) > 0:
        print("OCR Result is ", result[0], ".")
    else :
        print("Alert: OCR Result showing it is an empty iamge! ")
    # ocr_result is a matlab object, need to convert or extract information from it
    
    image_char = cv.imread(address);
    cv.namedWindow('Character', cv.WINDOW_AUTOSIZE)
    cv.imshow('Character',image_char)
    # cv.waitKey();

    #
    # This recognization accuracy is extremaly bad 
    #
    answer = input("Do you think it is correct? (y/n)")
    while (1) :
        if answer.lower() == "y":
            # do something
            break
        elif answer.lower() == "n":
            # do something
            break
        else:
            answer = input("Invalid input, please try again. (y/n)")

mat_eng.quit()

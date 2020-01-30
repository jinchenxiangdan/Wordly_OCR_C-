# MATLAB test running time: self time: 38.491s , total time 64.412s 
#
# Alert: Need MATLAB running during run this code
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


#---------------------------------------------------#
# functions                                         #
#---------------------------------------------------#

# returns the relative path according to the file name
# dir_path is 'Chars_data/BWChars'
def getBWCharsPath(file_name):
    dirpath = 'Chars_data/BWChars'
    return os.path.join(dirpath, file_name)

def drawTable(character, accuracy):
    print("Character: ",character , "--", accuracy)
    

#---------------------------------------------------#
# end of function part                              #
#---------------------------------------------------#

#
# Purpose: Read images from file and use OCR to recoginize 
# characters After that, store correct recogonization information
# 
# Works with matlab function <ocr_matlab.m>
#

# clear command line
lambda:os.system('cls')

# initial dictionary 
analysis_data_key = [None] * 100
analysis_data_val = [None] * 100

# open a figure window
plt.figure()

# check the first 100 images 
mat_eng = matlab.engine.start_matlab()

for j in range(1, 100):
    address = getBWCharsPath("char%05d.pbm" % (j))
    #FOR TEST
    #
    #print("address is ", address)
    #
    
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
    
    image_char = cv.imread(address);
    cv.namedWindow('Character', cv.WINDOW_AUTOSIZE)
    cv.imshow('Character',image_char)

    #
    # This recognization accuracy is extremaly bad 
    #
    answer = input("Do you think it is correct? (y/n)")
    
    # store the accuracy if the asnwer of OCR is correct
    while (1) :
        if (answer.lower() == "y"):
            if len(result) > 0:
                # store the accoacy ONLY the image is NOT empty
                analysis_data_key.append(image_char)
                analysis_data_val.append(result[2])
                break
            else:
                # do nothing
                # Empty image is meanless for us
                break
        elif answer.lower() == "n":
            # do nothing
            break
        else:
            
            answer = input("Invalid input, please try again. (y/n)")

mat_eng.quit()


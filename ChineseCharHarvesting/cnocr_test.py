# This is a test for library "cnocr"
# cnocr is a library of chinese script recogonize in python3 


from cnocr import CnOcr

ocr = CnOcr()
res = ocr.ocr('/home/wan/Desktop/ShawnJin_Workspace/Images/tesseract_test_input/test_3.jpg')
print("output is ", res, ". ")

# This library temply doesn't support image format pbm. 
# accuracy of jpg and jpeg is 0%.

# abort it
#!/bin/bash

# Shawn Jin
# conert all pbm images in this folder to tiff format 

count=0

for FILE in $(ls -v *.pbm)
do 
    name=${FILE%%.*}
    # convert all pbm images to tiff format 
    # $(magick $FILE $name.tiff ) 
    
    # add white border to each tiff image
    # $(convert $name.tiff -bordercolor black -border 1 ${name}_b.tiff)
    
    # inverse tiff images (black <-> white)


    #  --psm value 
    #   6    Assume a single uniform block of text.
    #   7    Treat the image as a single text line.
    #   8    Treat the image as a single word.
    $(echo "No.$count": >> tesseract_4.0_out.out)
    $(tesseract $name.tiff stdout -l chi_tra --dpi 70 --psm 8 >> tesseract_4.0_out.out)

    # update count 
    ((count+=1))

    # check the first 100 iamge 
    if [ "$count" -eq 100 ]; then
        break
    fi

    echo "Done Image $count."
done 
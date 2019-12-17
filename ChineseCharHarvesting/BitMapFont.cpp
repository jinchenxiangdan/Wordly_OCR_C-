#include <iostream>

#include <string>
#include <cmath>
// Matlab
// #include <mex.h>

using namespace std;
 
class BitMapFont {


    public: 


        BitMapFont(string name_in, int size_in, string characters_in, double padding_in) {
            name        = name_in;
            size        = size_in;
            chacacters  = characters_in;
            padding     = padding_in;
            // down round size and padding
            size    = std::ceil(size);
            padding = std::ceil(padding);
            // create bitmap 
            int bitmap[chacacters.length()]; 
            // TODO: calculate the bitmap of characters. going to use the library of MATLAB.
            
        }

    private:
        // initial values 
        string  name        = "Courier New";
        int     size        = 32;
        string  chacacters  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890''ì!\"£$%&/()=?^è+òàù,.-<\\|;:_>*@#[]{}";
        double  padding     = 0.02 * size;
};


/* Author: Shawn Jin
 * 
 * This is a class with 4 values
 *      name        <char *>
 *      size        <int>
 *      characters  <char *>
 *      paddng      <double>
 *
 *
 *
 */
#include <string>
using namespace std;

class Font {

public:

    // initial the values 
    string  name;         
    int     size;
    string  characters;   
    double  padding;      
    
    Font();
    Font(string name_in, int size_in, string characters_in, double padding_in);
};

Font::Font(void) {
    name = "Courier New";
    size = 32;
    // Some characters deleted because illegal character : (�!\"�$%&/()=?^�+�??)
    characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890'',.-<\\|;:_>*@#[]{}";
    padding = 0.02 * size;
}

Font::Font(string name_in, int size_in, string characters_in, double padding_in)
{
    name = name_in;
    size = size_in;
    characters = characters_in;
    padding = padding_in;
}
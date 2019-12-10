/* Author: Shawn Jin
 * This file create a BitmapFont when be called. 
 * 
 * Input:   Name,
 *          Size,
 *          Characters,
 *          Padding
 *
 * Output:  BitmapFont
 *
 *
 */
// #include "mex.h"
// 
// 
// void mexFunction(int nlhs, mxArray *plhs[],
//                 int nrhs, mxArray *prhs[]) {
// 
//     // check the number of input values 
//     if (nrhs != 4)
//         mexErrMsgTxt("Error: Invalid number of input arguments.\n");
//     // check the number of input values 
//     if (nlhs != 1)
//         mexErrMsgTxt("Error: Invalid number of output arguments.\n");
//     
//     
//     
// }

#include "mex.hpp"
#include "mexAdapter.hpp"

using namespace matlab::data;
using matlab::mex::ArgumentList;


class MexFunction : public matlab::mex::Function {
 
public :
    
    void operator() (ArgumentList outputs, ArguementList inputs) {
     
        // Validate arguments 
        checkArguments(outputs, inputs);
        // Implement function 
        outputs[0] = 4;
        outputs[1] = 2;
        
    }
    
private:
    
    void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
        ArrayFactory factory;
//         if (inputs[0].getType() != ArrayType::DOUBLE ||
//             inputs[0].getType() == ArrayType::COMPLEX_DOUBLE)
//         {
//             matlabPtr->feval(u"error", 0, 
//                 std::vector<Array>({ factory.createScalar("Input must be double array") }));
//         }
        if (inputs.size() != 4) {
            displayOnMATLAB("input size is invliad!");
        }
        if (inputs[0].getType() != ArrayType::MATLAB_STRING) {
        matlabPtr->feval(u"error", 0, 
                 std::vector<Array>({ factory.createScalar("Input must be string array") }));
            
//         }
// 
//         if (outputs.size() > 1) {
//             matlabPtr->feval(u"error", 0, 
//                 std::vector<Array>({ factory.createScalar("Only one output is returned") }));
//         }
    
        }
};
    
    
    
    
    
    
    
    
    
    
    
    
    
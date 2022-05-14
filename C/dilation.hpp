#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
/*
* Author: Group 5
* Date: 4/24/22
* Description: Header file for a dilation function. Takes in 2D vector and dilates all nonzero values with a [5,5] diamond-shaped mask
*/

namespace dilate {
    class dilation {
        public:
            //constructor for class 
            dilation();
            // performs dilation
            std::vector<std::vector<int>> dilate(std::vector<std::vector<int>> in);
    };
}

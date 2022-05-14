/*
 * Author: Group 5
 * Date Created: 4/19/22
 * This header file contains functions and variables for identifying cones from a filtered image.
 * Thus, this header file has functions that determine the regional maxes, perform dilation, and centroiding
 * to find the coordinates of the cones. 
 */

#ifndef MOR_PRO
#define MOR_PRO

#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiffio.h"
namespace mor_processing {
    class Cones {
        public:
            //constructor to make Cones object
            Cones();
            //pad_image pads the image with the value of the border of im (image) till size of rows and cols of the filter
            std::vector<std::vector<float>> pad_image(std::vector<std::vector<float>> im, int fil_rows, int fil_cols);
            //dilate dilates a binary image with a 3x3 all 1s structuring element 
            std::vector<std::vector<int>> dilate(std::vector<std::vector<int>> bw);
            //regional_max takes a 2-D std::vector of an image and idetnifies the regional maxima as 1s 
            //and returns the binary 2-D std::vector image with 0s where maxima are not found
            std::vector<std::vector<int>> regional_max(std::vector<std::vector<float>> im);
            //find_components finds the connected components or cones of the binary image bw and labels them with a count
            std::vector<std::vector<int>> find_components(std::vector<std::vector<int>> bw);
            //windowing windows the binary image according to the size of the filter
            std::vector<std::vector<float>> windowing(std::vector<std::vector<float>> name, int filter_rows, int filter_cols);
            
    };
}

#endif
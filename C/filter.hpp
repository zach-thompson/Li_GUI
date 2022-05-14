
/*
 * Author: Group 5
 * Date Created: 4/19/22
 * This header file contains functions and variables for loading TIFF files into a 2D array and a filtering function. 
 */
#ifndef FILT
#define FILT

#include "tiffio.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

namespace mor_processing {
    class Filter {
        public:
            //constructor to create object to use Filter class functions
            Filter();
            //load tiff image and output a 2d-vector with pixel values 
            std::vector<std::vector<float>> tiffToVector(const char * tiff_path);
            //take padded image and filters it with a ideal LP Gaussian filter 
            std::vector<std::vector<float>> filter_im(std::vector<std::vector<float>> im);
    };
}

#endif 


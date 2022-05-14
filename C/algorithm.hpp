/*
 * Author: Group 5
 * Date Created: 4/26/22
 * This header file contains the run function for implementing the entire algortihm.
 There is also a constructor for setting any parameters as specified by the user 
 */
#ifndef ALG
#define ALG

#include "morphological_processing.hpp"
#include "centroiding.hpp"
#include "dilation.hpp"
#include "filter.hpp"
#include <string>
#include <fstream>

namespace mor_processing {
    class Algorithm {
        public:
            //constructor to set the size/dimensions and path to TIFF image
            Algorithm(float dist, int rows, int cols, std::string filepath);
            //constructor to set the size/dimensions and cutoff distance of filter and path to TIFF image
            Algorithm(int rows, int cols, std::string filepath);
            //write_results writes the coordinates of the cones to the screen (a bash file will write it to a file)
            void write_results(std::vector<std::vector<float>> coords);
            //run runs the algorithm using the inputs from its constructor and outputting its result via a function within 
            void run();
            //setters and getters for private variables
            void set_dist(float dist);
            void set_rows(int rows);
            void set_cols(int cols);
            float get_dist();
            int get_rows();
            int get_cols();
        private:
            float filter_distance = 0; 
            int filter_rows = 0;
            int filter_cols = 0;
            std::string filepath;

    };
}


#endif
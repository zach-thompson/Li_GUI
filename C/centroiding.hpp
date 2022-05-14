/*
 * Author: Group 5
 * Date Created: 4/20/22
 * This header file contains functions for identifying the center of mass of connected components. 
 */

#ifndef CENTER
#define CENTER

#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

namespace mor_processing {
    class Centroids {
        public:
            //constructor to use Centroids functions
            Centroids();
            //calc_center_mass calculates the center of mass of the foreground objects from a connected components image
            //and it returns a binary image with 1s at the center of mass of objects 
            std::vector<std::vector<float>> calc_center_mass(std::vector<std::vector<int>> bw);
            //calc_avg_dist takes in the coordinates of the centroids and determines the nearest distance between each cone
            //those nearest distances are then averaged and returned 
            float calc_avg_dist(std::vector<std::vector<float>> coords);
    };
}
#endif
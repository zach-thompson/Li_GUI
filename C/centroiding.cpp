#include "centroiding.hpp"
//constructor
mor_processing::Centroids::Centroids() {

}
std::vector<std::vector<float>> mor_processing::Centroids::calc_center_mass(std::vector<std::vector<int>> bw) {
    //determine number of components in connected components image (max)
    int max = 0;
    for(int i=0; i<bw.size(); i++) {
        for(int j=0; j<bw[i].size(); j++) {
            if(bw[i][j] > max) {
                max = bw[i][j];
            }
        }
    }
    std::vector<std::vector<float>> coords(max, std::vector<float>(2,0)); //store final coordinates (indices)
    std::vector<int> x; //store x coordinates
    std::vector<int> y; //store y coordinates
    float sum = 0; //help calculate maxima below
    float mean_x = 0; float mean_y = 0;
    int k = 0; //increment through coordinates
    for(int comp = 1; comp <= max; comp++) { //find each component
        //go through entire image to find entirity of each component
        for(int i=0; i<bw.size(); i++) {
            for(int j=0; j<bw[i].size(); j++) {
                if(bw[i][j] == comp) {
                    x.push_back(j);
                    y.push_back(i);
                }
            }
        }
        /*
        for (int elm : x) {
            std::cout << elm << " ";
        }
        std::cout << "\n";
        for (int elm : y) {
            std::cout << elm << " ";
        }
        std::cout << "\n";
        */
        //found entire component and stored all coordinates of the component pixels
        //calculate center of mass by calculating average of coordinates
        for(int i=0; i<x.size(); i++) {
            sum = sum + x[i];
        }
        mean_x = sum/x.size();
        //std::cout << "x mean= " << mean_x << "\n";
        sum=0;
        for(int i=0; i<y.size(); i++) {
            sum = sum + y[i];
        }
        mean_y = sum/y.size();
        sum=0;
        //store coordinates
        coords[k][0] = mean_x;
        //std::cout << "x mean= " << mean_x << "\n";
        coords[k][1] = mean_y;
        //std::cout << "y mean= " << mean_y << "\n";
        k++;
        //clear for each new component
        x.clear();
        y.clear();

    }
    return coords;
}

float mor_processing::Centroids::calc_avg_dist(std::vector<std::vector<float>> coords) {
    float min_dist = 100; //random number... holds nearest distance 
    float dist = 0; //holds each calculated distance
    float sum = 0; //for calculating mean 
    //take each cone and calculate its distance from every other cone
    for(int i=0; i < coords.size(); i++) { //go through each row = cone's x and y coordinates
        for(int j=0; j < coords.size(); j++) { //go through all other cones except oneself 
            //calculate distance
            dist = sqrt(pow(coords[j][0]-coords[i][0], 2) + pow(coords[j][1]-coords[i][1], 2));
            
            if ((j != i) && dist < min_dist) { //don't include when calculate distance against self
                min_dist = dist;
            }
        }
        //once determine min/nearest distance of a cone, add to sum
        
        sum = min_dist + sum;
        min_dist = 100; //reset distance 

    }
    //calculate mean 
    return sum/coords.size(); //number of rows=number of cones/coordinates

}


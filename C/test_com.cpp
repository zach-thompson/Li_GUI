#include "morphological_processing.hpp"
#include "centroiding.hpp"

//main function to test mor proc functions 
int main(void) {
     std::vector<std::vector<float>> im
    {
        {2, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 2},
        {0, 0, 0, 0, 1, 0, 0, 0, 1}
    };
    //test regional_max function
    mor_processing::Cones cone;
    std::vector<std::vector<int>> bw = cone.regional_max(im);
    for (std::vector<int> rows : bw) {
        for (int x : rows) {
            //print out pixel (for testing)+
            std::cout << x << " ";

        }
        std::cout << "\n";
    }
    bw = cone.dilate(bw);
    //print out result
    for (std::vector<int> rows : bw) {
        for (int x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }

    bw = cone.find_components(bw);
    //print out result
    for (std::vector<int> rows : bw) {
        for (int x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }
    mor_processing::Centroids centroid;
    std::vector<std::vector<float>> coordinates = centroid.calc_center_mass(bw);
    //print out result
    std::cout << "centroids\n";
    for (std::vector<float> rows : coordinates) {
        for (float x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }
    float mean = centroid.calc_avg_dist(coordinates);
    std::cout << "mean = " << mean << "\n";
    return 0;
}
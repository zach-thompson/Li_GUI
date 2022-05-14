#include "morphological_processing.hpp"

//main function to test mor proc functions 
int main(void) {
     std::vector<std::vector<float>> im
    {
        {2, 1, 0, 7, 0, 0, 4, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 2},
        {5, 0, 3, 8, 1, 0, 0, 0, 6}
    };
    for (std::vector<float> rows : im) {
        for (float x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }
    //test regional_max function
    mor_processing::Cones cone;
    std::vector<std::vector<float>> pad = cone.pad_image(im, 5, 5);
    std::cout << "padded image \n";
    for (std::vector<float> rows : pad) {
        for (float x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }
    std::vector<std::vector<float>> win = cone.windowing(pad, 5, 5);
    std::cout << "windowed image \n";
    for (std::vector<float> rows : win) {
        for (float x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }
    std::vector<std::vector<int>> bw = cone.regional_max(win);
    std::cout << "regional max \n";
    for (std::vector<int> rows : bw) {
        for (int x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }
    

    bw = cone.find_components(bw);
    //print out result
    std::cout << "find components \n";
    for (std::vector<int> rows : bw) {
        for (int x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }


    return 0;
}

#ifndef FILT2
#define FILT2

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

namespace filter {
    class Filtering {
        public:
        Filtering();
        //vector<vector<float>> filter(TIFF* im_in, vector<vector<float>> filt);
        vector<std::vector<float>> filter(vector<std::vector<float>> im_in, vector<vector<float>> filt);
    };
}

#endif
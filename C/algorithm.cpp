#include "algorithm.hpp"
using namespace std;
mor_processing::Algorithm::Algorithm(float dist, int rows, int cols, std::string filepath) {
    this->filter_distance = dist;
    this->filter_rows = rows;
    this->filter_cols = cols;
    this->filepath = filepath;
}
mor_processing::Algorithm::Algorithm(int rows, int cols, std::string filepath) {
    this->filter_rows = rows;
    this->filter_cols = cols;
    this->filepath = filepath;
}
void mor_processing::Algorithm::write_results(std::vector<std::vector<float>> coords) {
    for (std::vector<float> rows : coords) {
        for (float x : rows) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}
void mor_processing::Algorithm::run() {
    int its = 0; //algorithm iterates twice to improve the cutoff frequency of filter 
    std::vector<std::vector<float>> coordinates; //size is determined by variable returned by centroiding function
    mor_processing::Cones cone;
    mor_processing::Centroids centroid;
    dilate::dilation dil;
    mor_processing::Filter filt;
    
    //float mean = 0;
    //while (its < 2) {
        
    //first load in file 
    std::vector<std::vector<float>> im = filt.tiffToVector(filepath.c_str());
    
    //pad image
    std::vector<std::vector<float>> padded_im = cone.pad_image(im, this->filter_rows, this->filter_cols);

    //cout << "about to filter \n";
    //filter image
    std::vector<std::vector<float>> filt_im = filt.filter_im(padded_im);

    //cout << "about to window \n";
    //window image
    std::vector<std::vector<float>> wind_im = cone.windowing(padded_im, this->filter_rows, this->filter_cols);
    
    //regional max
    std::vector<std::vector<int>> reg_max = cone.regional_max(wind_im);

    //cout << "about to dilate\n";
    //dilation by disk
    std::vector<std::vector<int>> dilated_bw = dil.dilate(reg_max);

    //cout << "about to find components\n";
    //find all components and label
    std::vector<std::vector<int>> labelled_im = cone.find_components(dilated_bw);
    //cout << "about to centroid\n";
    //centroiding
    std::vector<std::vector<float>> centroids = centroid.calc_center_mass(labelled_im);
        //mean nearest distance -> feeds into filter parameters 
        //mean = centroid.calc_avg_dist(centroids);
        //its++;
    //}
    for (std::vector<float> rows : centroids) {
        for (float x : rows) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}

void mor_processing::Algorithm::set_dist(float dist) {
    this->filter_distance = dist;
}
void mor_processing::Algorithm::set_rows(int rows){
    this->filter_rows = rows;
}
void mor_processing::Algorithm::set_cols(int cols) {
    this->filter_cols = cols;
}
float mor_processing::Algorithm::get_dist() {
    return this->filter_distance;
}
int mor_processing::Algorithm::get_rows() {
    return this->filter_rows;
}
int mor_processing::Algorithm::get_cols() {
    return this->filter_cols;
}
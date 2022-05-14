#include "dilation.hpp"
/*
* Author: Group 5
* Date: 4/24/22
* Description: Dilates nonzero values in a 2D vector with a set mask
*/
dilate::dilation::dilation() {
	
}
/*
* This function returns a 2D vector after performing a dilation with a 5x5 structure.
* @param in: 2D vector
*/

std::vector<std::vector<int>> dilate::dilation::dilate(std::vector<std::vector<int>> in) {
	// Create filter structure
	std::vector<std::vector<int>> filter = { {0, 0, 1, 0, 0},
                         					 {0, 1, 1, 1, 0},
                         					 {1, 1, 1, 1, 1},
						 					 {0, 1, 1, 1, 0},
						 					 {0, 0, 1, 0, 0} };

	// Create 2D array full of 0's to hold output
	int rows = in.size();
	int cols = in[0].size();

	std::vector<std::vector<float>> se { //dilation structuring element 
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    std::vector<float> neighborhood; 
    //pad image with black 1 pixel wide border white = 1 black = 0
    std::vector<std::vector<int>> padded_bw(in.size()+4, std::vector<int>(in[1].size()+4,0));
    int x = 0; int y = 0; //track indices of original bw
    for(int i=2; i<(padded_bw.size()-2); i++) {
        for(int j=2; j<(padded_bw[i].size()-2); j++) {
            //std::cout << y << "\n";
            padded_bw[i][j] = in[y][x];
            x++;
        }
        x=0;
        y++;
    }
	std::vector<std::vector<int>> out(rows, std::vector<int> (cols));
	
	//perform dilation algorithm
    float max = 0; //hold maximum of neighborhood
    int g = 0; int h = 0; //keep track of indices for final image
    int a = 0; int b = 0; //index throughout neighborhood
    for(int i=2; i<(padded_bw.size()-2); i++) {
        for(int j=2; j<(padded_bw[i].size()-2); j++) { //ignore edges
            //extract neighborhood for each pixel
            for (int y=0; y<filter.size(); y++) {
                for (int x=0; x<filter[y].size(); x++) {
                    a = (-(filter.size()-1)/2)+y;
                    //std::cout << "a = " << a << "\n";
                    b = (-(filter[y].size()-1)/2)+x;
                    //std::cout << "b = " << b << "\n";
                    if (((a+i)<padded_bw.size()) && ((j+b)<padded_bw[i].size()) && ((i+a)>=0) && ((j+b)>=0) && (filter[y][x]==1)) {
                        neighborhood.push_back(padded_bw[i+a][j+b]);
                    }
                    
                }
            }
            //determine maximum of neighborhood
            for (float neighbor : neighborhood) {
                if(neighbor > max) {
                    max = neighbor;
                }
            }
            //determine if should dilate
            //determine if regional max 
            if(max == 1) {
                out[g][h] = 1;
            }
            else { //not regional max
                out[g][h] = 0;
            }
            h++; //increment to next column 
            max = 0; //reset max for next neighborhood 
            neighborhood.clear(); //clear for next neighborhood
        }
        h=0; //reset to first column
        g++; //increment to next row
    }

	return out;
}
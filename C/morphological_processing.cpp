#include "morphological_processing.hpp"
#include <algorithm>
//constructor to make Cones object
mor_processing::Cones::Cones() {
    //std::cout << "made object!\n";
}
std::vector<std::vector<float>> mor_processing::Cones::pad_image(std::vector<std::vector<float>> im, int fil_rows, int fil_cols) {
    int i = 0; int j = 0; int x = 0; int y = 0;
    int pad_rows = fil_rows/2;
    int pad_cols = fil_cols/2;
    std::vector<std::vector<float>> padded_im(im.size()+2*pad_rows, std::vector<float>(im[1].size()+2*pad_cols,0)); 
    //fill corner with top left most pixel
    for( i = 0; i<pad_rows; i++) {
        for(j = 0; j<pad_cols; j++) {
            padded_im[i][j] = im[y][x];
        }
    }
    
    i = 0; j = 0; //reset i and j
    //fill padded_im with entire im between its border 
    for(i=pad_rows; i<(padded_im.size()-pad_rows); i++) {
        for(j=pad_cols; j<(padded_im[i].size()-pad_cols); j++) {
            //std::cout << y << "\n";
            padded_im[i][j] = im[y][x];
            x++;
        }
        x=0;
        y++;
    }
    
    //fill top right corner  
    for( i = 0; i<pad_rows; i++) {
        for(j = im[i].size()+pad_cols; j<padded_im[i].size(); j++) {
            padded_im[i][j] = im[0][im[0].size()-1];
        }
    }
    
    //fill bottom left corner 
    for( i = im.size()+pad_rows; i<padded_im.size(); i++) {
        for(j = 0; j<pad_cols; j++) {
            padded_im[i][j] = im[im.size()-1][0];
        }
    }

    //fill bottom right corner 
    for( i = im.size()+pad_rows; i<padded_im.size(); i++) {
        for(j = im[0].size()+pad_cols; j<padded_im[0].size(); j++) {
            padded_im[i][j] = im[im.size()-1][im[0].size()-1];
        }
    }
    
    //top portion
    x = 0;
    for(i = 0; i < pad_rows; i++) {
        for(j = pad_cols; j<im[0].size()+pad_cols; j++) {
            padded_im[i][j] = im[0][x];
            x++;
        }
        x=0;
    }
    
    //bottom portion
    x = 0;
    for(i = im.size()+pad_rows; i < padded_im.size(); i++) {
        for(j = pad_cols; j<im[0].size()+pad_cols; j++) {
            padded_im[i][j] = im[im.size()-1][x];
            x++;
        }
        x=0;
    }
    
    //left side
    x = 0;
    for(i = pad_rows; i < im.size()+pad_rows; i++) {
        for(j = 0; j<pad_cols; j++) {
            padded_im[i][j] = im[x][0];
            
        }
        x++;
    }
    
    //right side
    x = 0;
    for(i = pad_rows; i < im.size()+pad_rows; i++) {
        for(j = im[0].size()+pad_cols; j<padded_im[0].size(); j++) {
            padded_im[i][j] = im[x][im[0].size()-1];
            
        }
        x++;
    }
    
    
    return padded_im;
}
//dilate image based upon structuring element 
std::vector<std::vector<int>> mor_processing::Cones::dilate(std::vector<std::vector<int>> bw) {
    std::vector<std::vector<float>> se { //dilation structuring element 
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    std::vector<float> neighborhood; 
    //pad image with black 1 pixel wide border white = 1 black = 0
    std::vector<std::vector<int>> padded_bw(bw.size()+2, std::vector<int>(bw[1].size()+2,0));
    int x = 0; int y = 0; //track indices of original bw
    for(int i=1; i<(padded_bw.size()-1); i++) {
        for(int j=1; j<(padded_bw[i].size()-1); j++) {
            //std::cout << y << "\n";
            padded_bw[i][j] = bw[y][x];
            x++;
        }
        x=0;
        y++;
    }
    //will store dilated image 
    std::vector<std::vector<int>> dilated_im(bw.size(), std::vector<int>(bw[1].size(),0));
    //perform dilation algorithm
    float max = 0; //hold maximum of neighborhood
    int g = 0; int h = 0; //keep track of indices for final image
    int a = 0; int b = 0; //index throughout neighborhood
    for(int i=1; i<(padded_bw.size()-1); i++) {
        for(int j=1; j<(padded_bw[i].size()-1); j++) { //ignore edges
            //extract neighborhood for each pixel
            for (int y=0; y<se.size(); y++) {
                for (int x=0; x<se[y].size(); x++) {
                    a = (-(se.size()-1)/2)+y;
                    //std::cout << "a = " << a << "\n";
                    b = (-(se[y].size()-1)/2)+x;
                    //std::cout << "b = " << b << "\n";
                    if (((a+i)<padded_bw.size()) && ((j+b)<padded_bw[i].size()) && ((i+a)>=0) && ((j+b)>=0)) {
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
                dilated_im[g][h] = 1;
            }
            else { //not regional max
                dilated_im[g][h] = 0;
            }
            h++; //increment to next column 
            max = 0; //reset max for next neighborhood 
            neighborhood.clear(); //clear for next neighborhood
        }
        h=0; //reset to first column
        g++; //increment to next row
    }
    return dilated_im;
     

    
}
//determines regional maxima of image 
std::vector<std::vector<int>> mor_processing::Cones::regional_max(std::vector<std::vector<float>> im) {
    //implement connected components algorithm where maxima are pixels with a constant intensity surrounded by pixels with lower intensities
    
    //holds binary image (result of regional max)
    std::vector<std::vector<int>> bw(im.size(), std::vector<int>(im[1].size(),0));
    // structing element to extract neighborhood
    std::vector<std::vector<float>> se {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    float max = 0; //holds maximum of neighborhood
    int a = 0; int b = 0;
    std::vector<float> neighborhood; //hold neighborhood of each pixel 
    for (int i=0; i<im.size(); i++) { //go through each row
        for (int j=0; j<im[i].size(); j++) { //go through each column
            //extract neighborhood of each pixel based upon the se dimensions
            //std::cout << "made it to first paired loop!\n";
            for (int y=0; y<se.size(); y++) {
                for (int x=0; x<se[y].size(); x++) {
                    a = (-(se.size()-1)/2)+y;
                    b = (-(se[y].size()-1)/2)+x;
                    if (((a+i)<im.size()) && ((j+b)<im[i].size()) && ((i+a)>=0) && ((j+b)>=0)) {
                        //std::cout << "neighbor = " << im[i+a][j+b] << "\n";
                        neighborhood.push_back(im[i+a][j+b]);
                    }
                    
                }
            }
            //made neighborhood
        
            //find max of neighborhood
            for (float neighbor : neighborhood) {
                if(neighbor > max) {
                    max = neighbor;
                }
            }
            //determine if regional max 
            if(max == im[i][j] && max != 0) {
                bw[i][j] = 1;
            }
            else { //not regional max
                bw[i][j] = 0;
            }
            //constructs entire binary image 
            neighborhood.clear(); //clear neighborhood std::vector for next pixel         
            max = 0;

        }
    }

    return bw; 
}

std::vector<std::vector<int>> mor_processing::Cones::find_components(std::vector<std::vector<int>> bw) {
    //input: binary image with regional maxima dilated by a binary disk
    std::vector<std::vector<float>> se { //assumes 8-neighbor connectivity 
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    std::vector<float> neighborhood; 
    //pad image with black 1 pixel wide border white = 1 black = 0
    std::vector<std::vector<int>> padded_bw(bw.size()+2, std::vector<int>(bw[1].size()+2,0));
    int x = 0; int y = 0; //track indices of original bw
    for(int i=1; i<(padded_bw.size()-1); i++) {
        for(int j=1; j<(padded_bw[i].size()-1); j++) {
            //std::cout << y << "\n";
            padded_bw[i][j] = bw[y][x];
            x++;
        }
        x=0;
        y++;
    }
    //perform connected components algorithm 

    //x and x_new used for comparison
    std::vector<std::vector<int>> x_vect(padded_bw.size(), std::vector<int>(padded_bw[1].size(),0));
    std::vector<std::vector<int>> x_new(padded_bw.size(), std::vector<int>(padded_bw[1].size(),0));
    std::vector<std::vector<int>> x_dil(padded_bw.size(), std::vector<int>(padded_bw[1].size(),0));
    //used for counting components 
    std::vector<std::vector<int>> count_im(padded_bw.size(), std::vector<int>(padded_bw[1].size(),0));
    int num_comp_flag = 0; //flag for finding a connected component
    int k = 0; //use for iterating through component
    int num_comps = 0; //keep track of number of connected components
    for(int i=1; i< (padded_bw.size()-1); i++) { //ignore borders 
        for(int j=1; j<(padded_bw[i].size()-1); j++) {
            //check if already part of component first
            if(count_im[i][j] == 0) { //not already part of component
                //find first seed point 
                if(padded_bw[i][j] == 1) {
                    x_vect[i][j] = 1; //seed pt at where component is first found
                }
                k = 0; //reset for each component
                //loop to complete connected component
                while(x_vect != x_new) {
                        if (k >= 1) {
                            x_vect = x_new; //last iteration x result becomes current x
                        }
                        //dilate x_vect
                        x_dil = dilate(x_vect); 
                        //compare each element to determine if connected
                        for(int o=0; o < x_vect.size(); o++) {
                            for(int p=0; p < x_vect[o].size(); p++) {
                                x_new[o][p] = padded_bw[o][p] & x_dil[o][p]; //dilated image & thresholded image
                            }
                        }
                        k++; //increment iteration
                }

                //add component to final labelled binary image
                for(int o=0; o < x_new.size(); o++) {
                    for(int p=0; p < x_new[o].size(); p++) {
                        if(x_new[o][p] == 1) {
                            if(num_comp_flag == 0) {
                                //found new component!!
                                num_comps++;
                                num_comp_flag = 1;
                            }
                            count_im[o][p] = num_comps;
                         }
                
                                
                    }
                }
                //reset x_new and x to all 0s
                for(int o=0; o < x_new.size(); o++) {
                    for(int p=0; p < x_new[o].size(); p++) {
                        x_vect[o][p] = 0;
                        x_new[o][p] =0;
                    }
                }
                //reset flag
                num_comp_flag = 0;

            }

        }
        
    }

    //window count_im back to original size of bw 
    std::vector<std::vector<int>> win_count_im(bw.size(), std::vector<int>(bw[1].size(),0));
    x = 0; y = 0; //track indices of original bw
    for(int i=1; i<(count_im.size()-1); i++) {
        for(int j=1; j<(count_im[i].size()-1); j++) {
            win_count_im[y][x] = count_im[i][j];
            x++;
        }
        x=0;
        y++;
    }
    return win_count_im;

}

std::vector<std::vector<float>> mor_processing::Cones::windowing(std::vector<std::vector<float>> name, int filter_rows, int filter_cols) {
    int pad_rows = filter_rows/2;
    int pad_cols = filter_cols/2;
    std::vector<std::vector<float>> windowed(name.size()-2*pad_rows, std::vector<float>(name[0].size()-2*pad_cols,0));
    int x = pad_cols; int y = pad_rows;

    for(int i=0; i<(name.size()-2*pad_rows); i++) {
        for(int j=0; j<(name[i].size()-2*pad_cols); j++) {
            windowed[i][j] = name[y][x];
            x++;
        }
        x=pad_cols;

        y++;

    }
    return windowed;
}
/*
//implement Moore Neighbor Contour Tracing Algorithm 
//invert image for the Moore Neighbor tracing algorithm 
for (int i=0; i<bw.size(); i++) { //go through each row
    for (int j=0; j<bw[i].size(); j++) { 
        if(bw[i][j] == 1) {
            bw[i][j] = 0;
        }
        else {
            bw[i][j] = 1;
        }
    }
}
//pad image with white 1 pixel wide border white = 1 black = 0
std::vector<std::vector<float>> padded_bw(bw.size()+2, std::vector<float>(bw[1].size()+2,1));
//put in bw image within the border
int x = 0; int y = 0; //track indices of original bw
//std::cout << padded_bw.size() << "\n"; //number of rows 
//std::cout << padded_bw[1].size() << "\n"; //number of columns
for(int i=1; i<(padded_bw.size()-1); i++) {
    for(int j=1; j<(padded_bw[i].size()-1); j++) {
        //std::cout << y << "\n";
        padded_bw[i][j] = bw[y][x];
        x++;
    }
    x=0;
    y++;
}
//scan from top left postion for each pixel ignoring the borders
for(int i=1; i<(padded_bw.size()-1); i++) {
    for(int j=1; j<(padded_bw[i].size()-1); j++) {
        if(padded_bw[i][j] == 0) { //found a black pixel 
            //trace around contour in a clockwise direction


        }
    }
}
*/
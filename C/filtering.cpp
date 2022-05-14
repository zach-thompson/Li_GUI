#include "tiffio.h"
//#include "/home/anyamaradiaga/li/li/C/opencv2/imgproc"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include "filter.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    /*
    TIFF* tif= TIFFOpen("/home/ggibson/li/Dataset/hey.tif", "r");
    
    //check if tif is open
    if(tif) {
        int width, height; //height and width of TIFF image
        uint32* raster; //hold pixel value data
        
        //get size of the tiff
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
        int npixels = width*height; //total num of pixels

        raster = (uint32*)_TIFFmalloc(npixels*sizeof(uint32)); //allocate temp memory 

        if(raster == NULL) { //check memory is allocated
            TIFFClose(tif);
			cout << "Could not allocate memory for raster of TIFF image";
			return -1;
        }
        //check if tif read to the raster correctly 
        if(!TIFFReadRGBAImage(tif, width, height, raster, 0)) {
            TIFFClose(tif);
            cout << "Could not read raster of TIFF image";
            return -1;
        }
        //iterate through all pixels in the tif
        int red, green, blue; //hold each color channel
        vector<vector<float>> tiff_im(height, vector<float>(width,0));
        for(int i=0; i < width; i++) {
            for(int j=0; j < height; j++) {
                //cout << raster[j*width+i] << "\n";
                red = TIFFGetR(raster[j*width+i]);
                green = TIFFGetG(raster[j*width+i]);
                blue = TIFFGetB(raster[j*width+i]);
                //don't care about opacity with A?
                //take average of colors 
                tiff_im[j][i] = (red+green+blue)/3;
                //cout <<  tiff_im[j][i] << "\n";


            }
        }
        /* //for testing purposes 
        for (std::vector<float> rows : tiff_im) {
        for (float x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
        
    }
    */
   /*
    cout << width << "\n";
    cout << height <<"\n";
    }
    TIFFClose(tif);
    */
   /*
    ifstream inputfile("kernel.txt");
    int row = 15, col = 15;
    vector<vector<float>> kernel(row, vector<float>(col,0));
    //error checking
    if (!inputfile.is_open()) {
        cout <<"Error opening file\n";
    }
    for(int i=0; i < row; i++) {
        for(int j=0; j < col; j++) {
            inputfile >> kernel[i][j];
        }
    }*/
    mor_processing::Filter filt;
    std::vector<std::vector<float>> im = filt.tiffToVector(argv[1]);
    for (std::vector<float> rows : im) {
        for (float x : rows) {
            //print out pixel (for testing)
            std::cout << x << " ";

        }
        std::cout << "\n";
    }
    return 0;

};

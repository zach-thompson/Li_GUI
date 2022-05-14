#include "filter.hpp"
#include <fstream>
using namespace std;

mor_processing::Filter::Filter() {
    //does nothing except construct the object
}
//load tiff image and output a 2d-vector with pixel values 
std::vector<std::vector<float>> mor_processing::Filter::tiffToVector(const char* tiff_path) {
    TIFF* tif= TIFFOpen(tiff_path, "r");
    int red, green, blue; //hold each color channel
    int width, height; //height and width of TIFF image
    uint32* raster; //hold pixel value data
        
    //get size of the tiff
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
    vector<vector<float>> tiff_im(height, vector<float>(width,0));
    
    //check if tif is open
    if(tif) {
        
        int npixels = width*height; //total num of pixels

        raster = (uint32*)_TIFFmalloc(npixels*sizeof(uint32)); //allocate temp memory 
        //error checking follows below 
        if(raster == NULL) { //check memory is allocated
            TIFFClose(tif);
			cout << "Could not allocate memory for raster of TIFF image";
			return tiff_im; //all zeros
        }
        //check if tif read to the raster correctly 
        if(!TIFFReadRGBAImage(tif, width, height, raster, 0)) {
            TIFFClose(tif);
            cout << "Could not read raster of TIFF image";
            return tiff_im; //all zeros 
        }
        //iterate through all pixels in the tif
        
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
    }
    TIFFClose(tif);
    return tiff_im;
}
//take padded image and filters it with a ideal LP Gaussian filter 
std::vector<std::vector<float>> mor_processing::Filter::filter_im(std::vector<std::vector<float>> im) {
    //read in kernel file (kernel.txt)
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
    }
    //kernel fully loaded to be used for convolution
    int rows_im = im.size();
	int cols_im = im[0].size();
    int rows_filt = kernel.size();
	int cols_filt = kernel[0].size();
    vector<vector<float>> im_out(rows_im, vector<float> (cols_im,0));
    int a,b; 
    int sum = 0; 
    
	for (int i = 7; i < rows_im-7; i++) { // Scans through the array, minus the border values
		for (int j = 7; j < cols_im-7; j++) {
            for (int u = 0; u < rows_filt; u++) { 
		        for (int v = 0; v < cols_filt; v++) {
                    a=(-(rows_filt-1)/2)+u;
                    //cout << a << "\n";
                    b=(-(cols_filt-1)/2)+v;
                    //cout << b << "\n";
                    sum += im[i+a][j+b]*kernel[u][v];
                }
            }
            im_out[i][j] = sum;
            sum = 0; 
        }

    }
    return im_out;


}

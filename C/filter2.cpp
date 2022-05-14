#include "filter2.hpp"

vector<std::vector<float>> filter::Filtering::filter(vector<vector<float>> im_in, vector<vector<float>> filt){
    int rows_im = im_in.size();
	int cols_im = im_in[0].size();
    int rows_filt = filt.size();
	int cols_filt = filt[0].size();
    vector<vector<float>> im_out(rows_filt, vector<float> (cols_filt));
    int a,b; 
    //vector<vector<float>> image; 
    //im_in = image; 
 
    int sum = 0; 
    
	for (int i = 0; i < rows_im; i++) { // Scans through the array, minus the border values
		for (int j = 0; j < cols_im; j++) {
            for (int u = 0; u < rows_filt; i++) { 
		        for (int v = 0; v < cols_filt; j++) {
                    a=(-(rows_filt-1)/2)-1+i;
                    b=(-(cols_filt-1)/2)-1+j;
                    sum += im_in[i][j]*filt[u][v];
                }
            }
            im_out[i][j] = sum;
            sum = 0; 
        }

    }
    return im_out;
}


#include "dilation.hpp"
/*
* Author: Group 5
* Date: 4/24/22
* Description: Dilates nonzero values in a 2D vector with a set mask
*/
dilate::dilation::dilation() { }

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
	std::vector<std::vector<int>> out(rows, std::vector<int> (cols));
	
	// Perform the dilation process
	for (int i = 2; i < rows - 2; i++) { // Scans through the array, minus the border values
		for (int j = 2; j < cols - 2; j++) {
			if (in[i][j] != 0) { // Loop runs if value isn't 0
				for (int a = -2; a < 3; a++) { // Runs through the neighboring indices 
					for (int b = -2; b < 3; b++) {
						out[i + a][j + b] = in[i][j] * filter[a + 1][b + 1]; // Applies the filter
					}
				}
			}
		}
	}

	return out;
}
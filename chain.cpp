/**
 * @file block.cpp
 * @description Student implementation of Block functions, CPSC 221 PA1
 * @author (your CWLs here)
**/

#include "block.h"
#include <cmath>
#include <iostream>

/**
 * Return the dimension(width or height) of the block.
**/
int Block::Dimension() const {
	if (data.empty()) { return 0; } // if there is no image
	return data.size(); // since rows & columns are the same, return one of them
}

/**
 * Renders the given block onto img with its upper
 * left corner at (x, y). Assumes the rendered block fits on the
 * image.
 * The block is enlarged using nearest-neighbour scaling
 * (i.e. no pixel blending).
 * @pre scale >= 1
**/
void Block::Render(PNG& img, int x, int y, int scale) const {
	// loop through block
	for (int i = x; i < x + Dimension(); i++) {
		for (int j = y; j < y + Dimension(); j++) {
			RGBAPixel * colour = data[i][j]; // get colour from block
            RGBAPixel * pixel = img.getPixel(i,j);
            pixel->r = colour->r;
            pixel->g = colour->g;
            pixel->b = colour->b;
			
		}
	}
}

/**
 * Creates a block that is dimension X dimension pixels in size
 * by copying the pixels from (x, y) to (x+dimension-1, y+dimension-1)
 * in img. Assumes img is large enough to supply these pixels.
**/
void Block::Build(PNG& img, int x, int y, int dimension) {
	// redimension the block vector to (dimension x dimension)
	data.resize(dimension); // row
	for (auto& row : data) { // column
    	row.resize(dimension);
	}

	for (int i = x; i < x+dimension; i++) {
		for (int j = y; j < y+dimension; j++) {
			RGBAPixel pixel = *img.getPixel(i + x, j + y); // get RGBAPixel value from img
			data[i - x][j - y] = pixel; // append to block from (0,0) to (dimension-1, -)
		}
	}

}

/**
 * Rearranges the image data in this Block so that it is transposed
 * (flipped) over the diagonal line from upper-left to lower-right
 * e.g.  1 2 3      1 4 7
 *       4 5 6  ->  2 5 8
 *       7 8 9      3 6 9
**/
void Block::Transpose() {
	
	// create copy of data
	vector<vector<RGBAPixel>> arr = data;

	// assumes that data is a (n x n) matrix
	for (int i = 0; i < Dimension(); i++) { 
		for (int j = 0; j < Dimension(); j++) {
			data[i][j] = arr[j][i]; // transpose
		}
	}

}

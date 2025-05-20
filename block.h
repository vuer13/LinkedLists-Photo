#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
using namespace std;
using namespace cs221util;

class Block {

	public:
		/** 
		 * Creates a block that is width X img.height pixels in size
		 * by copying the pixels from (x, 0) to (x+width-1, img.height-1)
		 * in img. Assumes img is large enough to supply these pixels.
		 */
		void Build(PNG &img, int x, int width);

		/**
		 * Renders the given block onto img with its upper
		 * left corner at (x, 0). Assumes block fits on the 
		 * image.
		 */
		void Render(PNG &img, int x) const;

		// Return the width and height of the block.
		int Width() const;
		int Height() const;

		// Return distance between rightmost column of this (leftBlock)
		// and leftmost column of rightBlock
		double DistanceTo(Block const & rightBlock) const; // GIVEN
   
	private:
		vector<vector<RGBAPixel>> data;
};

#endif

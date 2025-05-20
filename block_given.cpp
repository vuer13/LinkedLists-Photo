#include "block.h"

/**
 * Given functions for the Block class.
 *
 * ****WARNING****
 *
 * You should not modify this file.  It is not one of the files
 * you will submit.  We will grade your submission using the
 * original version of this file.
 */

// Return "distance" between rightmost column of this (leftBlock)
// and leftmost column of rightBlock
double Block::DistanceTo(Block const & rightBlock) const {
	int h = Height();
	int w = Width();
	double d = 0.0;
	for( int y=0; y<h; ++y ) {
		if (data[w - 1][y].dist(rightBlock.data[0][y]) > 0.01) d = d + 1;
	}
	d = d/h;
	return d;
}

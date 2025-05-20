/**
 * @file main.cpp
 * Split an image into k vertical strips (blocks), 
 * rearrange the blocks into a random order,
 * write the concatenation of the blocks into a new image,
 * unscramble the new image back into the original.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "chain.h"
#include <iostream>
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;

int main() {
	/**
	 * Use your own images and other tests to test your code!
	 * Some tests you should write:
	 * 1) building and rendering blocks
	 * 2) copying a chain
	 * 3) assigning one chain to another
	 * 4) swapping Nodes in a chain
	 * 5) unscrambling an image
	 * NOTE: Your code should not be able to correctly unscramble
	 * bc.png.  Why not?
	 */
	PNG im;
	im.readFromFile("images-given/sun.png");
	//im.readFromFile("images-given/terrain.png");
	//im.readFromFile("images-given/wg.png");
	//im.readFromFile("images-given/kg.png");
	Chain c(im, 5);
	// randomly scramble the blocks.
	c.Scramble();
	// or test swapping a few blocks
	//  c.TestSwap(3,4); // swap the 3rd and 4th blocks.
	//  c.TestSwap(0,1);
	//  c.TestSwap(0,3);
	//  c.TestSwap(4,3);

	c.Render().writeToFile("images-output/scram.png");  // look at scram.png to debug

	// test unscramble()
	c.Unscramble();
	c.Render().writeToFile("images-output/unscram.png");// look at unscram.png also

	/* Check that unscramble works to unscramble a *saved* image too. */
	//PNG om;
	//om.readFromFile("images-given/scram.png");
	//Chain d(om, 5);
	//d.Unscramble();
	//d.Render().writeToFile("images-output/unscram-from-file.png");
	
	return 0;
}

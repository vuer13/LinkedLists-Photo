#include "block.h"
#include <cmath>
#include <iostream>

int Block::Height() const {
	return data.empty() ? 0 : data[0].size();
}

int Block::Width() const {
    return data.size();
}

void Block::Render(PNG &im, int x) const {
	for (unsigned int w = 0; w < data.size(); w++) {
        for (unsigned int h = 0; h < data[w].size(); h++) {
            *im.getPixel(x + w, h) = data[w][h];
        }
    }
}

void Block::Build(PNG &im, int x, int width) {
	unsigned int height = im.height();
    data.clear();
    data.resize(width, vector<RGBAPixel>(height));

    for (int w = 0; w < width; w++) {
        for (unsigned int h = 0; h < height; h++) {
            data[w][h] = *im.getPixel(x + w, h);
        }
    }
}

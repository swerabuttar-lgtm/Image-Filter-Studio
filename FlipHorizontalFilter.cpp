#include "FlipHorizontalFilter.h"

FlipHorizontalFilter::FlipHorizontalFilter() : Filter("Flip Horizontal", "Geometric") {}

void FlipHorizontalFilter::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth()/2; j++) {
            Pixel temp = img.at(i, j);
            img.at(i, j) = img.at(i, img.getWidth()-1-j);
            img.at(i, img.getWidth()-1-j) = temp;
        }
}
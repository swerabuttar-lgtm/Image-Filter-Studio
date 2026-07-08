#include "FlipVerticalFilter.h"

FlipVerticalFilter::FlipVerticalFilter() : Filter("Flip Vertical", "Geometric") {}

void FlipVerticalFilter::apply(Image& img) {
    for (int i = 0; i < img.getHeight()/2; i++)
        for (int j = 0; j < img.getWidth(); j++) {
            Pixel temp = img.at(i, j);
            img.at(i, j) = img.at(img.getHeight()-1-i, j);
            img.at(img.getHeight()-1-i, j) = temp;
        }
}
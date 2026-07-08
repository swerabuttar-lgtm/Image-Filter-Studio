#include "InvertFilter.h"

InvertFilter::InvertFilter() : Filter("Invert", "Pixel Transform") {}

void InvertFilter::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
            img.at(i,j) = Pixel(
                255 - img.at(i,j).getR(),
                255 - img.at(i,j).getG(),
                255 - img.at(i,j).getB());
}
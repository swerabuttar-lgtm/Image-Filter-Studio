#include "GrayscaleFilter.h"

GrayscaleFilter::GrayscaleFilter() : Filter("Grayscale", "Pixel Transform") {}

void GrayscaleFilter::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++) {
            int avg = (img.at(i,j).getR() + img.at(i,j).getG() + img.at(i,j).getB()) / 3;
            img.at(i,j) = Pixel(avg, avg, avg);
        }
}
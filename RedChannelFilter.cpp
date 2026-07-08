#include "RedChannelFilter.h"

RedChannelFilter::RedChannelFilter() : Filter("Red Channel Only", "Pixel Transform") {}

void RedChannelFilter::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
            img.at(i,j) = Pixel(img.at(i,j).getR(), 0, 0);
}
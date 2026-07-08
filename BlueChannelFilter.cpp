#include "BlueChannelFilter.h"

BlueChannelFilter::BlueChannelFilter() : Filter("Blue Channel Only", "Pixel Transform") {}

void BlueChannelFilter::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
            img.at(i,j) = Pixel(0, 0, img.at(i,j).getB());
}
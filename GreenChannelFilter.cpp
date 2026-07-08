#include "GreenChannelFilter.h"

GreenChannelFilter::GreenChannelFilter() : Filter("Green Channel Only", "Pixel Transform") {}

void GreenChannelFilter::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
            img.at(i,j) = Pixel(0, img.at(i,j).getG(), 0);
}
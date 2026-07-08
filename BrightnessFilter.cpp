#include "BrightnessFilter.h"

BrightnessFilter::BrightnessFilter(int amount) 
    : Filter("Brightness Adjust", "Pixel Transform"), amount(amount) {}

void BrightnessFilter::apply(Image& img) {
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
            img.at(i,j) = Pixel(
                Pixel::clamp(img.at(i,j).getR() + amount),
                Pixel::clamp(img.at(i,j).getG() + amount),
                Pixel::clamp(img.at(i,j).getB() + amount));
}

string BrightnessFilter::getDescription() const {
    return "Brightness Adjust (" + to_string(amount) + ")";
}
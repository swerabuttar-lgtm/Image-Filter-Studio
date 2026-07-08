#include "ContrastFilter.h"

ContrastFilter::ContrastFilter() : Filter("Contrast Stretch", "Pixel Transform") {}

void ContrastFilter::apply(Image& img) {
    int minV = 255, maxV = 0;
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++) {
            int r = img.at(i,j).getR();
            int g = img.at(i,j).getG();
            int b = img.at(i,j).getB();
            if (r < minV) minV = r;
            if (g < minV) minV = g;
            if (b < minV) minV = b;
            if (r > maxV) maxV = r;
            if (g > maxV) maxV = g;
            if (b > maxV) maxV = b;
        }
    if (maxV == minV) return;
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++)
            img.at(i,j) = Pixel(
                (img.at(i,j).getR()-minV)*255/(maxV-minV),
                (img.at(i,j).getG()-minV)*255/(maxV-minV),
                (img.at(i,j).getB()-minV)*255/(maxV-minV));
}
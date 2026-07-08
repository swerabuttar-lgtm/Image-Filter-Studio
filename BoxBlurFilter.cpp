#include "BoxBlurFilter.h"

BoxBlurFilter::BoxBlurFilter() : Filter("Box Blue (3x3)", "Spatial Filter") {}

void BoxBlurFilter::apply(Image& img) {
    Image copy(img);
    for (int i = 0; i < img.getHeight(); i++)
        for (int j = 0; j < img.getWidth(); j++) {
            int r=0, g=0, b=0, count=0;
            for (int di=-1; di<=1; di++)
                for (int dj=-1; dj<=1; dj++) {
                    int ni=i+di, nj=j+dj;
                    if (ni>=0 && ni<img.getHeight() && nj>=0 && nj<img.getWidth()) {
                        r += copy.at(ni,nj).getR();
                        g += copy.at(ni,nj).getG();
                        b += copy.at(ni,nj).getB();
                        count++;
                    }
                }
            img.at(i,j) = Pixel(r/count, g/count, b/count);
        }
}
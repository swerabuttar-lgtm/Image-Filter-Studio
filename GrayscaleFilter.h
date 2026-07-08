#pragma once
#include "Filter.h"
#include "Image.h"

class GrayscaleFilter : public Filter {
public:
    GrayscaleFilter();
    void apply(Image& img) override;
};
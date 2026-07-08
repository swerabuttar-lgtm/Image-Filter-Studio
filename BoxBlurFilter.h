#pragma once
#include "Filter.h"
#include "Image.h"

class BoxBlurFilter : public Filter {
public:
    BoxBlurFilter();
    void apply(Image& img) override;
};
#pragma once
#include "Filter.h"
#include "Image.h"

class FlipVerticalFilter : public Filter {
public:
    FlipVerticalFilter();
    void apply(Image& img) override;
};
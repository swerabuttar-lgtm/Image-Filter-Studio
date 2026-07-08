#pragma once
#include "Filter.h"
#include "Image.h"

class FlipHorizontalFilter : public Filter {
public:
    FlipHorizontalFilter();
    void apply(Image& img) override;
};
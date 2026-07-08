#pragma once
#include "Filter.h"
#include "Image.h"

class GreenChannelFilter : public Filter {
public:
    GreenChannelFilter();
    void apply(Image& img) override;
};
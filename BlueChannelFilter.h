#pragma once
#include "Filter.h"
#include "Image.h"

class BlueChannelFilter : public Filter {
public:
    BlueChannelFilter();
    void apply(Image& img) override;
};
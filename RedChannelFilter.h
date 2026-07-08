#pragma once
#include "Filter.h"
#include "Image.h"

class RedChannelFilter : public Filter {
public:
    RedChannelFilter();
    void apply(Image& img) override;
};
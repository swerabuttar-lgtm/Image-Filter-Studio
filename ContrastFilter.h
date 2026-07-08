#pragma once
#include "Filter.h"
#include "Image.h"

class ContrastFilter : public Filter {
public:
    ContrastFilter();
    void apply(Image& img) override;
};
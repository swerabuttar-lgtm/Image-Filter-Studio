#pragma once
#include "Filter.h"
#include "Image.h"

class InvertFilter : public Filter {
public:
    InvertFilter();
    void apply(Image& img) override;
};
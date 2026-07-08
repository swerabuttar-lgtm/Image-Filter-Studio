#pragma once
#include "Filter.h"
#include "Image.h"

class BrightnessFilter : public Filter {
    int amount;
public:
    BrightnessFilter(int amount);
    void apply(Image& img) override;
    string getDescription() const override;
};
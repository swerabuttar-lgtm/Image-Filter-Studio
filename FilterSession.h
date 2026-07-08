#pragma once
#include "Image.h"
#include "Filter.h"
#include <string>
using namespace std;

const int MAX_FILTERS = 20;

class FilterSession {
private:
    string customerCnic;
    Image* image;
    Filter* pipeline[MAX_FILTERS];
    int filterCount;

public:
    FilterSession(string cnic);
    ~FilterSession();

    void run();
    void loadImage();
    void buildPipeline();
    void applyPipeline();
    void saveResult();
    FilterSession& addFilter(Filter* f);  // method chaining
};
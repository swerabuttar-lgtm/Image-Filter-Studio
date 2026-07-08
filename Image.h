#pragma once
#include "Pixel.h"
#include <string>
using namespace std;

class FilterSession;

class Image {
private:
    Pixel** grid;
    int width;
    int height;
    friend class FilterSession;
public:
    Image(int width, int height);
    Image(const Image& other);
    ~Image();
    Pixel& at(int row, int col);
    const Pixel& at(int row, int col) const;
    int getWidth() const;
    int getHeight() const;
    bool loadFromFile(const string& path);
    bool saveToFile(const string& path) const;
    void displayASCII() const;
    void fillTestPattern();
};
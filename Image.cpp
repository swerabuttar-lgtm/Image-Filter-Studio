#include "Image.h"
#include <iostream>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

Image::Image(int width, int height) : width(width), height(height) {
    cout << "[Image] Constructor called" << endl;
    grid = new Pixel*[height];
    for (int i = 0; i < height; i++)
        grid[i] = new Pixel[width];
}

Image::Image(const Image& other) : width(other.width), height(other.height) {
    cout << "[Image] Copy Constructor called" << endl;
    grid = new Pixel*[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new Pixel[width];
        for (int j = 0; j < width; j++)
            grid[i][j] = other.grid[i][j];
    }
}

Image::~Image() {
    cout << "[Image] Destructor called" << endl;
    for (int i = 0; i < height; i++)
        delete[] grid[i];
    delete[] grid;
}

Pixel& Image::at(int row, int col) { return grid[row][col]; }
const Pixel& Image::at(int row, int col) const { return grid[row][col]; }
int Image::getWidth() const { return width; }
int Image::getHeight() const { return height; }

bool Image::loadFromFile(const string& path) {
    int w, h, channels;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 3);
    if (!data) {
        cout << "ERROR: Could not load: " << path << endl;
        return false;
    }
    for (int i = 0; i < height; i++) delete[] grid[i];
    delete[] grid;
    width = w; height = h;
    grid = new Pixel*[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new Pixel[width];
        for (int j = 0; j < width; j++) {
            int idx = 3*(i*width+j);
            grid[i][j] = Pixel(data[idx], data[idx+1], data[idx+2]);
        }
    }
    stbi_image_free(data);
    cout << "Loaded: " << width << "x" << height << endl;
    return true;
}

bool Image::saveToFile(const string& path) const {
    unsigned char* data = new unsigned char[width*height*3];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            int idx = 3*(i*width+j);
            data[idx]   = grid[i][j].getR();
            data[idx+1] = grid[i][j].getG();
            data[idx+2] = grid[i][j].getB();
        }
    int result = stbi_write_png(path.c_str(), width, height, 3, data, width*3);
    delete[] data;
    if (result) { cout << "Saved: " << path << endl; return true; }
    cout << "ERROR saving." << endl;
    return false;
}

void Image::displayASCII() const {
    int dW = min(width, 60);
    int dH = min(height, 25);
    cout << "\n=== ASCII Preview (" << width << "x" << height << ") ===\n";
    for (int i = 0; i < dH; i++) {
        for (int j = 0; j < dW; j++)
            cout << grid[i][j].toASCII();
        cout << "\n";
    }
    cout << "Size: " << width << "x" << height << "\n\n";
}

void Image::fillTestPattern() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            int r = (j*255)/width;
            int g = (i*255)/height;
            grid[i][j] = Pixel(r, g, 128);
        }
}
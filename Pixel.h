#pragma once
#include <iostream>
using namespace std;

class Pixel {
private:
    int r, g, b;
public:
    Pixel();
    Pixel(int r, int g, int b);
    int getR() const;
    int getG() const;
    int getB() const;
    void setR(int r);
    void setG(int g);
    void setB(int b);
    static int clamp(int value);
    Pixel operator+(const Pixel& other) const;
    friend ostream& operator<<(ostream& os, const Pixel& p);
    char toASCII() const;
};
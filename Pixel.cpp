#include "Pixel.h"

Pixel::Pixel() : r(0), g(0), b(0) {}

Pixel::Pixel(int r, int g, int b) {
    this->r = clamp(r);
    this->g = clamp(g);
    this->b = clamp(b);
}

int Pixel::getR() const { return r; }
int Pixel::getG() const { return g; }
int Pixel::getB() const { return b; }

void Pixel::setR(int r) { this->r = clamp(r); }
void Pixel::setG(int g) { this->g = clamp(g); }
void Pixel::setB(int b) { this->b = clamp(b); }

int Pixel::clamp(int value) {
    if (value < 0) return 0;
    if (value > 255) return 255;
    return value;
}

Pixel Pixel::operator+(const Pixel& other) const {
    return Pixel(clamp(r+other.r), clamp(g+other.g), clamp(b+other.b));
}

ostream& operator<<(ostream& os, const Pixel& p) {
    os << "(" << p.r << "," << p.g << "," << p.b << ")";
    return os;
}

char Pixel::toASCII() const {
    int brightness = (r + g + b) / 3;
    if (brightness < 32)  return ' ';
    if (brightness < 64)  return '.';
    if (brightness < 96)  return ':';
    if (brightness < 128) return '-';
    if (brightness < 160) return '=';
    if (brightness < 192) return '+';
    if (brightness < 224) return '*';
    if (brightness < 240) return '#';
    return '@';
}
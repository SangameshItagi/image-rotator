#include <cmath>
#include "colorPixel.h"

ColorPixel::ColorPixel(){}
ColorPixel::ColorPixel(int red_, int green_, int blue_){
    this->red=red_;
    this->green=green_;
    this->blue=blue_;
}
ColorPixel::~ColorPixel(){}

int ColorPixel::getRed() {return red;}
int ColorPixel::getGreen() {return green;}
int ColorPixel::getBlue() {return blue;}
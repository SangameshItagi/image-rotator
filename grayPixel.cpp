#include <cmath>
#include "grayPixel.h"

GrayPixel::GrayPixel() {}
GrayPixel::GrayPixel(int grayPixel_){ this->grayPixel=grayPixel_;}
GrayPixel::~GrayPixel(){}
int GrayPixel::getGrayPixel() {return grayPixel;}
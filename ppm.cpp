#include <cmath>
#include <string>
#include "ppm.h"

PPM::PPM(){}
PPM::PPM(string magicNumber, int height, int width, int maxValue, vector<ColorPixel> colorPixels){
    this->magicNumber=magicNumber;
    this->height=height;
    this->width=width;
    this->maxValue=maxValue;
    this->colorPixels=colorPixels;
}
PPM::~PPM(){}

string PPM::getMagicNumber(){return magicNumber;}
int PPM::getHeight(){return height;}
int PPM::getWidth(){return width;}
int PPM::getMaxValue(){return maxValue;}
vector<ColorPixel> PPM::getColorPixels(){return colorPixels;}

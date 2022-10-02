#include <cmath>
#include <string>
#include "pgm.h"
#include <vector>

PGM::PGM(){}
PGM::PGM(string magicNumber, int height, int width, int maxValue, vector<GrayPixel> grayPixels){
    this->magicNumber=magicNumber;
    this->height=height;
    this->width=width;
    this->maxValue=maxValue;
    this->grayPixels=grayPixels;
}
PGM::~PGM(){}

string PGM::getMagicNumber(){return magicNumber;}
int PGM::getHeight(){return height;}
int PGM::getWidth(){return width;}
int PGM::getMaxValue(){return maxValue;}
vector<GrayPixel> PGM::getGrayPixels(){return grayPixels;}
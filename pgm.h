#ifndef PGM_H_
#define PGM_H_
#include <vector>
#include <string>
#include "grayPixel.h"
using namespace std;
class PGM 
{
	private:
        string magicNumber;
		int height;
        int width;
        int maxValue;
        vector<GrayPixel> grayPixels;


	public:
        PGM();
        PGM(string magicNumber, int height, int width, int maxValue, vector<GrayPixel> grayPixels);
        ~PGM();

        string getMagicNumber();
		int getHeight();
        int getWidth();
        int getMaxValue();
        vector<GrayPixel> getGrayPixels();
};

#endif // PGM_H_
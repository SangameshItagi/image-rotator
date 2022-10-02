#ifndef PPM_H_
#define PPM_H_
#include <string>
#include <vector>
#include "colorPixel.h"
using namespace std;
class PPM 
{
	private:
        string magicNumber;
		int height;
        int width;
        int maxValue;
        vector<ColorPixel> colorPixels;

	public:
        PPM();
        PPM(string magicNumber, int height, int width, int maxValue, vector<ColorPixel> colorPixels);
        ~PPM();
        string getMagicNumber();
		int getHeight();
        int getWidth();
        int getMaxValue();
        vector<ColorPixel> getColorPixels();
};

#endif // PPM_H_
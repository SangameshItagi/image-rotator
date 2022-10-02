#ifndef GRAY_PIXEL_H_
#define GRAY_PIXEL_H_

class GrayPixel 
{
	private:
		int grayPixel;

	public:
        GrayPixel();
        GrayPixel(int grayPixel_);
        ~GrayPixel();
        
		int getGrayPixel();
};

#endif // GRAY_PIXEL_H_
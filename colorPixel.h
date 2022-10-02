#ifndef COLOR_PIXEL_H_
#define COLOR_PIXEL_H_

class ColorPixel 
{
	private:
		int red;
        int green;
        int blue;

	public:
        ColorPixel();
        ColorPixel(int red_, int green_, int blue_);
        ~ColorPixel();

		int getRed();
		int getGreen();
		int getBlue();
};

#endif // COLOR_PIXEL_H_
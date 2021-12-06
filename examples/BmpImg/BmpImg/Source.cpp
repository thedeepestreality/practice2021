#include <iostream>
#include "BmpStructures.h"
#include "ImgFunctions.h"

int main()
{
	printImgInfo("masterpiece.bmp");
	RgbImg img = readRgbImg("masterpiece.bmp");
	for (size_t row=0; row < 50;++row)
		for (size_t col = 0; col < 50; ++col)
		{
			img.pixels[row][col].Red = 255;
			img.pixels[row][col].Blue = 255;
			img.pixels[row][col].Green = 255;
		}

	writeRgbImg("ugly_copy.bmp", img);

	for (size_t row = 0; row < img.height; ++row)
		delete[] img.pixels[row];
	delete[] img.pixels;
	return 0;
}
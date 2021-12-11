#include <iostream>
#include "BmpStructures.h"
#include "ImgFunctions.h"

void testBmpIo()
{
	printImgInfo("masterpiece.bmp");
	RgbImg img = readRgbImg("masterpiece.bmp");
	for (size_t row=0; row < 50;++row)
		for (size_t col = 0; col < 50; ++col)
		{
			img.pixels[row][col].Blue = 255;
			img.pixels[row][col].Green = 128;
			img.pixels[row][col].Red = 0;
			//img.pixels[row][col] = {255, 255, 255}; //same as above
		}
	writeRgbImg("out\\ugly_copy.bmp", img);
	deleteRgbImg(img);
}

//Generate dummy image example
void genImgWithSquare()
{
	RGB background = { 255, 128, 0 };
	RgbImg img = createRgbImg(600, 600, background);
	for (size_t row = 50; row < 200; ++row)
		for (size_t col = 100; col < 400; ++col)
			img.pixels[row][col] = { 128, 255, 0 };

	writeRgbImg("out\\ai_masterpiece.bmp", img);
	deleteRgbImg(img);
}

//Autobalancing example
void testAutolevels()
{
	RgbImg img = readRgbImg("data\\Lenna.bmp");
	RgbImg balanced = autolevels(img);
	writeRgbImg("out\\Lenna_avtolevels.bmp", img);
	deleteRgbImg(img);
}

//Another autobalancing example
void testGrayworld()
{
	RgbImg img = readRgbImg("data\\sinichka.bmp");
	RgbImg balanced = grayworld(img);
	writeRgbImg("out\\grayworld.bmp", balanced);
	deleteRgbImg(img);
}

//Box filter example
void testBoxFilter()
{
	RgbImg img = readRgbImg("data\\kidsnoise.bmp");
	RgbImg filtered = convolution(img, 5);
	writeRgbImg("out\\kids_filtered.bmp", img);
	deleteRgbImg(img);
	deleteRgbImg(filtered);
}

void testKernelFilter()
{
	size_t const kern_sz = 3;
	double** kernel = new double* [kern_sz];
	for (size_t row = 0; row < kern_sz; ++row)
	{
		kernel[row] = new double[kern_sz];
		for (size_t col = 0; col < kern_sz; ++col)
			kernel[row][col] = 1. / 9;
	}
	RgbImg img = readRgbImg("data\\kidsnoise.bmp");
	RgbImg filtered = convolution(img, 5, kernel);
	writeRgbImg("out\\kids_filtered_kernel.bmp", img);
	deleteRgbImg(img);
	deleteRgbImg(filtered);
}

void testContours()
{
	RgbImg img = readRgbImg("data\\valve.bmp");
	RgbImg contour_img = contours(img);
	writeRgbImg("out\\contours.bmp", contour_img);
	deleteRgbImg(img);
	deleteRgbImg(contour_img);
}

int main()
{
	testContours();
	return 0;
}
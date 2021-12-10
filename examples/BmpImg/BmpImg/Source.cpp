#include <iostream>
#include "BmpStructures.h"
#include "ImgFunctions.h"

void genImgWithSquare()
{
	RgbImg img = { nullptr, 0, 0 };
	img.width = 600;
	img.height = 600;
	img.pixels = new RGB * [img.height];
	for (size_t row = 0; row < img.height; ++row)
	{
		img.pixels[row] = new RGB[img.width];
		for (size_t col = 0; col < img.width; ++col)
			img.pixels[row][col] = { 255, 128, 0 };
	}

	for (size_t row = 50; row < 200; ++row)
		for (size_t col = 100; col < 400; ++col)
			img.pixels[row][col] = { 128, 255, 0 };

	writeRgbImg("ai_masterpiece.bmp", img);
	deleteRgbImg(img);
}

int main()
{
	genImgWithSquare();
	//printImgInfo("masterpiece.bmp");
	//RgbImg img = readRgbImg("masterpiece.bmp");
	//for (size_t row=0; row < 50;++row)
	//	for (size_t col = 0; col < 50; ++col)
	//	{
	//		img.pixels[row][col].Red = 255;
	//		img.pixels[row][col].Blue = 255;
	//		img.pixels[row][col].Green = 255;
	//	}

	//writeRgbImg("ugly_copy.bmp", img);

	//for (size_t row = 0; row < img.height; ++row)
	//	delete[] img.pixels[row];
	//delete[] img.pixels;
	return 0;
}
#include "ImgFunctions.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

RgbImg readRgbImg(const char* filename) 
{
    RgbImg img = { nullptr, 0, 0 };
    return img;
}

void writeRgbImg(char const* filename, RgbImg const& img) {}

void printImgInfo(const char* filename)
{
    std::ifstream bmp_in(filename, std::ios::binary);
    if (!bmp_in.is_open())
        throw std::runtime_error("Failed to open bmp file");

    BITMAPFILEHEADER bmp_file_info;
    bmp_in.read((char*)&bmp_file_info, sizeof(BITMAPFILEHEADER));

    std::cout << "File " << filename << "\n";
    std::cout << "Type: " << ((char*)&bmp_file_info.bfType)[0];
    std::cout << " " << ((char*)&bmp_file_info.bfType)[1] << "\n";
    std::cout << "File size: " << bmp_file_info.bfSize << "\n";
    std::cout << "Img offset: " << bmp_file_info.bfOffBits << "\n";

    BITMAPINFOHEADER bmp_img_info;
    bmp_in.read((char*)&bmp_img_info, sizeof(BITMAPINFOHEADER));
    
    std::cout << "Width: " << bmp_img_info.biWidth << "\n";
    std::cout << "Height: " << bmp_img_info.biHeight << "\n";
    std::cout << "Depth: " << bmp_img_info.biBitCount << "\n";

    bmp_in.close();
}

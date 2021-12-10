#include "ImgFunctions.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

void deleteRgbImg(RgbImg& img)
{
    size_t const height = img.height;
    for (size_t row = 0; row < height; ++row)
        delete[] img.pixels[row];
    delete[] img.pixels;
}

BYTE linearTransform(BYTE x, BYTE min1, BYTE max1, BYTE min2 = 0, BYTE max2 = 255)
{
    return (double)(x - min1) * (max2 - min2) / (max1 - min1) + min2;
}

void autolevels(RgbImg& img)
{
    BYTE b_min = img.pixels[0][0].Blue;
    BYTE b_max = b_min;
    BYTE g_min = img.pixels[0][0].Green;
    BYTE g_max = g_min;
    BYTE r_min = img.pixels[0][0].Red;
    BYTE r_max = r_min;

    size_t const height = img.height;
    size_t const width = img.width;

    for (size_t row = 0; row < height; ++row)
        for (size_t col = 0; col < width; ++col)
        {
            RGB const& color = img.pixels[row][col];
            if (color.Blue > b_max)
                b_max = color.Blue;
            if (color.Blue < b_min)
                b_min = color.Blue;
            if (color.Green > g_max)
                g_max = color.Green;
            if (color.Green < g_min)
                g_min = color.Green;
            if (color.Red > r_max)
                r_max = color.Red;
            if (color.Red < r_min)
                r_min = color.Red;
        }

    for (size_t row = 0; row < height; ++row)
        for (size_t col = 0; col < width; ++col)
        {
            BYTE& blue = img.pixels[row][col].Blue;
            blue = linearTransform(blue, b_min, b_max);
            BYTE& green = img.pixels[row][col].Green;
            green = linearTransform(green, g_min, g_max);
            BYTE& red = img.pixels[row][col].Red;
            red = linearTransform(red, r_min, r_max);
        }
}

int getOffset(int width)
{
    int offset = 0;
    if (width % 4 != 0)
        offset = 4 - (3 * width) % 4;
    return offset;
}

RgbImg readRgbImg(const char* filename) 
{
    std::ifstream bmp_in(filename, std::ios::binary);
    if (!bmp_in.is_open())
        throw std::runtime_error("Failed to open input bmp file");

    BITMAPFILEHEADER bmp_file_info;
    BITMAPINFOHEADER bmp_img_info;
    bmp_in.read((char*)&bmp_file_info, sizeof(BITMAPFILEHEADER));
    bmp_in.read((char*)&bmp_img_info, sizeof(BITMAPINFOHEADER));

    int const offset = getOffset(bmp_img_info.biWidth);
    RgbImg img;
    img.width = bmp_img_info.biWidth;
    img.height = bmp_img_info.biHeight;
    img.pixels = new RGB * [img.height];
    for (size_t row = 0; row < img.height; ++row)
    {
        img.pixels[row] = new RGB[img.width];
        for (size_t col = 0; col < img.width; ++col)
            bmp_in.read((char*)&img.pixels[row][col], 3);
        bmp_in.seekg(offset, std::ios::cur);
    }
    bmp_in.close();
    return img;
}

void writeRgbImg(char const* filename, RgbImg const& img) 
{
    std::ofstream bmp_out(filename, std::ios::binary);
    if (!bmp_out.is_open())
        throw std::runtime_error("Failed to open output bmp file");
    int offset = getOffset(img.width);
    BITMAPFILEHEADER bmp_file_info;
    char bfType[] = { 'B', 'M' };
    bmp_file_info.bfType = *((WORD*)bfType);
    bmp_file_info.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bmp_file_info.bfSize = bmp_file_info.bfOffBits + (img.height * (img.width + offset)) * 3;
    bmp_file_info.bfReserved1 = bmp_file_info.bfReserved2 = 0;

    BITMAPINFOHEADER bmp_img_info;
    bmp_img_info.biClrImportant = bmp_img_info.biClrUsed = bmp_img_info.biCompression = 0;
    bmp_img_info.biPlanes = bmp_img_info.biXPelsPerMeter = bmp_img_info.biYPelsPerMeter = 1;
    bmp_img_info.biSize = sizeof(BITMAPINFOHEADER);
    bmp_img_info.biSizeImage = bmp_file_info.bfSize - bmp_file_info.bfOffBits;
    bmp_img_info.biWidth = img.width;
    bmp_img_info.biHeight = img.height;
    bmp_img_info.biBitCount = 24;

    bmp_out.write((char*)&bmp_file_info, sizeof(BITMAPFILEHEADER));
    bmp_out.write((char*)&bmp_img_info, sizeof(BITMAPINFOHEADER));

    BYTE* offset_array = new BYTE [offset];
    for (size_t i = 0; i < offset; ++i)
        offset_array[i] = 0;

    for (size_t row = 0; row < img.height; ++row)
    {
        for (size_t col = 0; col < img.width; ++col)
            bmp_out.write((char*)&img.pixels[row][col], 3);
        bmp_out.write((char*)offset_array, offset);
    }
    
    delete[] offset_array;
    bmp_out.close();
}

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

#include "ImgFunctions.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

int getOffset(int width)
{
    int offset = 0;
    if (width % 4 != 0)
        offset = 4 - (3 * width) % 4;
    return offset;
}

RgbImg createRgbImg(size_t height, size_t width, RGB color)
{
    RgbImg img = { nullptr, height, width };
    img.pixels = new RGB * [img.height];
    for (size_t row = 0; row < img.height; ++row)
    {
        img.pixels[row] = new RGB[img.width];
        for (size_t col = 0; col < img.width; ++col)
            img.pixels[row][col] = color;
    }
    return img;
}

void deleteRgbImg(RgbImg& img)
{
    size_t const height = img.height;
    for (size_t row = 0; row < height; ++row)
        delete[] img.pixels[row];
    delete[] img.pixels;
}

RgbImg copyRgbImg(RgbImg const& img)
{
    RgbImg imgCopy = { nullptr, img.height, img.width };
    imgCopy.pixels = new RGB * [img.height];
    for (size_t row = 0; row < img.height; ++row)
    {
        imgCopy.pixels[row] = new RGB[img.width];
        for (size_t col = 0; col < img.width; ++col)
        {
            imgCopy.pixels[row][col].Red = img.pixels[row][col].Red;
            imgCopy.pixels[row][col].Blue = img.pixels[row][col].Blue;
            imgCopy.pixels[row][col].Green = img.pixels[row][col].Green;
        }
    }
    return imgCopy;
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

    BYTE* offset_array = new BYTE[offset];
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

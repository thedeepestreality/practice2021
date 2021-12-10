#pragma once
#include "BmpStructures.h"

//Utilities
RgbImg createRgbImg(size_t height, size_t width, RGB color = { 0,0,0 });
void deleteRgbImg(RgbImg& img);
RgbImg copyRgbImg(RgbImg const& img);
RgbImg readRgbImg(char const* filename);
void writeRgbImg(char const* filename, RgbImg const& img);
void printImgInfo(char const* filename);

//ColorBalancing
RgbImg autolevels(RgbImg const& img, size_t kern_sz = 0);
RgbImg grayworld(RgbImg const& img, size_t kern_sz = 0);

//Filtering
RgbImg convolution(RgbImg const& img, size_t kernel_size);
RgbImg convolution(RgbImg const& img, size_t kernel_size, double** kernel);
RgbImg contours(RgbImg const& img);
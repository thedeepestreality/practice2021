#include "ImgFunctions.h"
#include <cmath>

RgbImg convolution(RgbImg const& img, size_t kernel_size)
{
    size_t const kernel_count = kernel_size * kernel_size;
    double const kernel_el = 1. / kernel_count;
    double** kernel = new double* [kernel_size];
    for (size_t row = 0; row < kernel_size; ++row)
    {
        kernel[row] = new double[kernel_size];
        for (size_t col = 0; col < kernel_size; ++col)
            kernel[row][col] = kernel_el;
    }
    RgbImg result = convolution(img, kernel_size, kernel);
    for (size_t row = 0; row < kernel_size; ++row)
        delete[] kernel[row];
    delete[] kernel;
    return result;
}

RgbImg convolution(RgbImg const& img, size_t kernel_size, double** kernel)
{
    RgbImg imgCopy = copyRgbImg(img);
    size_t const height = img.height;
    size_t const width = img.width;
    size_t const half = kernel_size / 2;

    for (size_t row = half; row < height - half; ++row)
        for (size_t col = half; col < width - half; ++col)
        {
            double b_weighted_sum = 0;
            double g_weighted_sum = 0;
            double r_weighted_sum = 0;
            for (size_t k_row = 0; k_row < kernel_size; ++k_row)
                for (size_t k_col = 0; k_col < kernel_size; ++k_col)
                {
                    size_t const res_row = row + k_row - half;
                    size_t const res_col = col + k_col - half;
                    RGB const& pixel = img.pixels[res_row][res_col];
                    double kern_el = kernel[k_row][k_col];
                    b_weighted_sum += kern_el*pixel.Blue;
                    g_weighted_sum += kern_el*pixel.Green;
                    r_weighted_sum += kern_el*pixel.Red;
                }
            RGB& pixel = imgCopy.pixels[row][col];
            double blue = std::abs(b_weighted_sum);
            double green = std::abs(g_weighted_sum);
            double red = std::abs(r_weighted_sum);
            pixel.Blue = blue > 255 ? 255 : blue;
            pixel.Green = green > 255 ? 255 : green;
            pixel.Red = red > 255 ? 255 : red;
        }
    return imgCopy;
}

RgbImg contours(RgbImg const& img)
{
    size_t const kern_sz = 3;
    static double kern_hor[kern_sz][kern_sz] = {
    	{-1, 0, 1},
    	{-2, 0, 2},
    	{-1, 0, 1}
    };
    static double kern_ver[kern_sz][kern_sz] = {
    	{-1, -2, -1},
    	{ 0,  0,  0},
    	{ 1,  2,  1}
    };
    static double* ver_ptr[kern_sz] = { kern_hor[0], kern_hor[1], kern_hor[2] };
    static double* hor_ptr[kern_sz] = { kern_ver[0], kern_ver[1], kern_ver[2] };
    RgbImg imgCopyHor = convolution(img, kern_sz, hor_ptr);
    RgbImg imgCopyVer = convolution(img, kern_sz, ver_ptr);
    RgbImg result = copyRgbImg(img);
    for (size_t row = 0; row < img.height; ++row)
    	for (size_t col = 0; col < img.width; ++col)
    	{
    		RGB& c_h = imgCopyHor.pixels[row][col];
    		RGB& c_v = imgCopyVer.pixels[row][col];
    		RGB& c_r = result.pixels[row][col];

            double blue = sqrt((double)c_h.Blue * c_h.Blue + (double)c_v.Blue * c_v.Blue);
            double green = sqrt((double)c_h.Green * c_h.Green + (double)c_v.Green * c_v.Green);
            double red = sqrt((double)c_h.Red * c_h.Red + (double)c_v.Red * c_v.Red);

            c_r.Blue = blue > 255 ? 255 : blue;
            c_r.Green = green > 255 ? 255 : green;
            c_r.Red = red > 255 ? 255 : red;
    	}
    autolevels(result, kern_sz);
    return result;
}
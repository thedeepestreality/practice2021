#include "ImgFunctions.h"

BYTE linearTransform(BYTE x, BYTE min1, BYTE max1, BYTE min2 = 0, BYTE max2 = 255)
{
    return min2 + (double)(x - min1) * (max2 - min2) / (max1 - min1);
}

RgbImg autolevels(RgbImg const& img, size_t kern_sz)
{
    RgbImg out_img = createRgbImg(img.height, img.width);
    size_t half = kern_sz / 2;
    BYTE b_min = img.pixels[half][half].Blue;
    BYTE b_max = b_min;
    BYTE g_min = img.pixels[half][half].Green;
    BYTE g_max = g_min;
    BYTE r_min = img.pixels[half][half].Red;
    BYTE r_max = r_min;

    size_t const height = img.height;
    size_t const width = img.width;

    for (size_t row = half; row < height - half; ++row)
        for (size_t col = half; col < width - half; ++col)
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
            RGB& out_color = out_img.pixels[row][col];
            BYTE blue = img.pixels[row][col].Blue;
            out_color.Blue = linearTransform(blue, b_min, b_max);
            BYTE green = img.pixels[row][col].Green;
            out_color.Green = linearTransform(green, g_min, g_max);
            BYTE red = img.pixels[row][col].Red;
            out_color.Red = linearTransform(red, r_min, r_max);
        }
    return out_img;
}

RgbImg grayworld(RgbImg const& img, size_t kern_sz)
{
    RgbImg out_img = createRgbImg(img.height, img.width);
    size_t half = kern_sz / 2;
    size_t const height = img.height;
    size_t const width = img.width;
    size_t const count = width * height;
    double r_avg = 0;
    double g_avg = 0;
    double b_avg = 0;
    for (size_t row = half; row < height - half; ++row)
        for (size_t col = half; col < width - half; ++col)
        {
            RGB const& color = img.pixels[row][col];
            b_avg += (double)color.Blue / count;
            g_avg += (double)color.Green / count;
            r_avg += (double)color.Red / count;
        }
    double avg = (b_avg + g_avg + r_avg) / 3;
    double b_s = avg / b_avg;
    double g_s = avg / g_avg;
    double r_s = avg / r_avg;

    for (size_t row = 0; row < height; ++row)
        for (size_t col = 0; col < width; ++col)
        {
            RGB const& color = img.pixels[row][col];
            double blue = b_s * color.Blue;
            double green = g_s * color.Green;
            double red = r_s * color.Red;

            RGB& out_color = out_img.pixels[row][col];
            out_color.Blue = blue > 255 ? 255 : blue;
            out_color.Green = green > 255 ? 255 : green;
            out_color.Red = red > 255 ? 255 : red;
        }
    return out_img;
}
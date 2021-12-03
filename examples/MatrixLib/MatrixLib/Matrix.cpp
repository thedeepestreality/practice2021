#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

double** createMatrix(size_t rows, size_t cols)
{
    double** matrix = new double* [rows];
    for (size_t idx = 0; idx < rows; ++idx)
        matrix[idx] = new double[cols];
    return matrix;
}

void deleteMatrix(double** matrix, size_t rows, size_t cols)
{
    for (size_t idx = 0; idx < rows; ++idx)
        delete[] matrix[idx];
    delete[] matrix;
}

void inputMatrix(double** matrix, size_t rows, size_t cols)
{
    std::cout << "Input matrix with " << cols << " cols:\n";
    for (size_t r = 0; r < rows; ++r)
    {
        std::cout << "Input " << r << " row: ";
        for (size_t c = 0; c < cols; ++c)
            std::cin >> matrix[r][c];
    }
}

double** inputFileMatrix(char const* filename, size_t& rows, size_t& cols)
{
    std::ifstream in(filename);
    if (!in.is_open())
        throw std::runtime_error("Failed to open matrix file");
    in >> rows >> cols;
    double** matrix = createMatrix(rows, cols);
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            in >> matrix[r][c]; //*(*(matrix+r)+c)
    in.close();
    return matrix;
}

void printMatrix(double** matrix, size_t rows, size_t cols)
{
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
            std::cout << matrix[r][c] << '\t';
        std::cout << '\n';
    }
    std::cout << '\n';
}

void zeros(double** matrix, size_t rows, size_t cols)
{
    fill(matrix, rows, cols, 0);
}

void ones(double** matrix, size_t rows, size_t cols)
{
    fill(matrix, rows, cols, 1);
}

void fill(double** matrix, size_t rows, size_t cols, double val)
{
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            matrix[r][c] = val;
}

double** linspace(size_t length)
{
    double** vec = createMatrix(1, length);
    for (size_t idx = 0; idx < length; ++idx)
        vec[0][idx] = idx + 1;
    return vec;
}

double** transpose(double** matrix, size_t rows, size_t cols)
{
    double** transposed = createMatrix(cols, rows);
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            transposed[c][r] = matrix[r][c];
    return transposed;
}

template <typename Type>
void Swap(Type& a, Type& b)
{
    Type tmp = a;
    a = b;
    b = tmp;
}

void rotate180(double** matrix, size_t rows, size_t cols)
{
    // Step 1. reverse elements in each row
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols / 2; ++c)
            Swap(matrix[r][c], matrix[r][cols - c - 1]);

    ////Step 2. reverse rows
    for (size_t r = 0; r < rows / 2; ++r)
        Swap(matrix[r], matrix[rows - r - 1]);
}

double& findMinimum(double** matrix, size_t rows, size_t cols)
{
    double minimum = **matrix;
    size_t r_min = 0;
    size_t c_min = 0;
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            if (matrix[r][c] < minimum)
            {
                minimum = matrix[r][c];
                r_min = r;
                c_min = c;
            }
    return matrix[r_min][c_min];
}

double& minmaxMatrix(double** matrix, size_t rows, size_t cols)
{
    size_t r_min = 0;
    size_t c_min = 0;
    size_t r_max = 0;
    size_t c_max = 0;
    double minimum;
    double maximum;
    for (size_t r = 0; r < rows; ++r){
        minimum = matrix[r][0];
        r_min = r;
        c_min = 0;
        for (size_t c = 1; c < cols; ++c)
            if (matrix[r][c] < minimum){
                minimum = matrix[r][c];
                r_min = r;
                c_min = c;
            }
        if (r == 0 || minimum > maximum){
            maximum = minimum;
            r_max = r_min;
            c_max = c_min;
        }
    }
    return matrix[r_max][c_max];
}

void mixMatrix( double** matrix, 
                size_t rows, 
                size_t cols, 
                size_t k1, 
                size_t k2)
{
    if (k1 == k2) 
        return;
    if (k1 >= rows || k1 >= cols || k2 >= rows || k2 >= cols)
        return;
    Swap(matrix[k1], matrix[k2]);
    for (size_t r = 0; r < rows; ++r)
        Swap(matrix[r][k1], matrix[r][k2]);
}

void randMatrix(double** matrix, 
                size_t rows, 
                size_t cols, 
                double minval, 
                double maxval)
{
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            matrix[r][c] = ((maxval-minval)*rand()) / RAND_MAX + minval;
}

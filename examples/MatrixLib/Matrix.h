#pragma once

// Function that allocates memory for matrix
// Params:
//   rows -- number of matrix rows
//   cols -- number of matrix cols
// Return value:
//   pointer to matrix
// WARNING! Don't forget to delete memory
double** createMatrix(size_t rows, size_t cols);

///TODO: add documentation
void deleteMatrix(double** matrix, size_t rows, size_t cols);
void inputMatrix(double** matrix, size_t rows, size_t cols);
void printMatrix(double** matrix, size_t rows, size_t cols);
void zeros(double** matrix, size_t rows, size_t cols);
void ones(double** matrix, size_t rows, size_t cols);
void fill(double** matrix, size_t rows, size_t cols, double val = 0);
double** linspace(size_t length);

double** transpose(double** matrix, size_t rows, size_t cols);

//1 2 3 4   -> 12 11 10 9
//5 6 7 8   -> 8 7 6 5
//9 10 11 12-> 4 3 2 1
void rotate180(double** matrix, size_t rows, size_t cols);

double& findMinimum(double** matrix, size_t rows, size_t cols);
#include <iostream>
#include "Matrix.h"

int main()
{
    size_t const Rows = 3;
    size_t const Cols = 4;
    double** matrix = createMatrix(Rows, Cols);
    /*inputMatrix(matrix, Rows, Cols);
    printMatrix(matrix, Rows, Cols);*/
    zeros(matrix, Rows, Cols);
    printMatrix(matrix, Rows, Cols);

    ones(matrix, Rows, Cols);
    printMatrix(matrix, Rows, Cols);

    fill(matrix, Rows, Cols, -1.5);
    printMatrix(matrix, Rows, Cols);

    for (size_t r = 0; r < Rows; ++r)
        for (size_t c = 0; c < Cols; ++c)
            matrix[r][c] = r * Cols + c;
    printMatrix(matrix, Rows, Cols);

    rotate180(matrix, Rows, Cols);
    printMatrix(matrix, Rows, Cols);

    /*double& minimum = findMinimum(matrix, Rows, Cols);
    minimum = 42;*/
    findMinimum(matrix, Rows, Cols) = 42;
    printMatrix(matrix, Rows, Cols);

    double** vec = linspace(Cols);
    printMatrix(vec, 1, Cols);

    double** transposed = transpose(matrix, Rows, Cols);
    printMatrix(transposed, Cols, Rows);

    deleteMatrix(matrix, Rows, Cols);
    deleteMatrix(vec, 1, Cols);
    deleteMatrix(transposed, Rows, Cols);
    return 0;
}
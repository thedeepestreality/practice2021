#include <iostream>
#include "../MatrixLib/Matrix.h"

int main()
{
    size_t Rows;
    size_t Cols;
    double** matrix;
    try
    {
        matrix = inputFileMatrix("matrix.txt", Rows, Cols);
    }
    catch (std::exception& e)
    {
        std::cout << "Error happened: " << e.what() << "\n";
        return 1;
    }
    printMatrix(matrix, Rows, Cols);
    deleteMatrix(matrix, Rows, Cols);
    return 0;
}
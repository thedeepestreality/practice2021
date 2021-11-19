# Занятие 21-22

#### Задача 0.

Дописать в проект MatrixLib функции:

* Умножение матрицы на число  ```double** multMatrix(double lambda, double** M, size_t rows, size_t columns);```
* Сложение матриц  ```double** plusMatrix(double** A, double** B, size_t rows, size_t columns);```
* Вычитание матриц  ```double** minusMatrix(double** A, double** B, size_t rows, size_t columns);```
* Умножение матриц  ```double** multMatrix(double** A, double** B, size_t rowsA, size_t columnsA, size_t columnsB);```
* Функция возращает ссылку на максимальный элемент в матрице ```double& maximumMatrix(double** M, size_t rows, size_t columns);```
* Функция возращает ссылку на максимальный среди минимальных элементов строк матрицы ```double& minmaxMatrix(double** M, size_t rows, size_t columns);```
* Функция меняет местами строки матрицы с номерами K_1 и K_2 и столбцы с номерами K_1 и K_2  ```void mixMatrix(double** M, size_t rows, size_t columns, size_t K_1, size_t K_2);```

#### Задача 1.
Элемент матрицы называется ее локальным минимумом, если он меньше всех окружающих его элементов. 
Написать функцию ```localMinimum```, которая заменяет все локальные минимумы заданной матрицы на нули.

#### Задача 2.
Написать функцию, которая вычисляет определитель квадратной матрицы произвольной размерности.
```double det(double** M, size_t size);```

#### Задача 3.
Написать функцию, которая вычисляет обратную квадратной матрицы произвольной размерности.
```double inv(double** M, size_t size);```

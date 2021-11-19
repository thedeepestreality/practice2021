#### Задача 1.
Заполнить массив nxm (размеры вводит пользователь) числами от 1 до nm по змейке. Нечетные строки слева направо, чётные -- в обратном порядке.

#### Задача 2.
Заполнить массив nxm (размеры вводит пользователь)  случайными числами в диапазоне от 0 до 100000.
Вывести матрицу на экран, выровняв столбцы по левому краю. Например,
```
10    23456  13 
1013  12     145
1     234    7
40726 12     4567
```

## Функции

#### Задача 3.
Написать функцию `void snakeArray(int** A, int n)`, которая заполняет массив числами от 1 до n^2 по змейке.

#### Задача 4.
Написать функцию нахождения корня из числа с помощью метода Ньютона `double mysqrt(double x, double eps=1e-6);`

Вычисление осуществляется по формуле: $Z_{n+1} = Z_n - \frac{Z_n^2-x}{2 Z_n}$, $Z_0 = 1.0$.

Вычислять пока $|Z_{n+1} - Z_{n}|>\epsilon$.

#### Задача 5.
Заполнить массив nxm (размеры вводит пользователь) числами от 1 до nm по спирали (улитке).

#### Задача 6.
Заполнить массив nxm (размеры вводит пользователь) случайными числами в диапазоне от 0 до 100000.
Вывести матрицу на экран, выровняв столбцы по правому краю. Например,
```
   10 23456   13 
 1013    12  145
    1   234    7
40726    12 4567
```

#### Задача 7.
Написать функцию 
```
void shiftArray(int A[], int n, in k)
```
которая осуществляет циклический сдвиг элементов массива на k влево. 
Например, если был массив
```
A[10]= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
```
То после вызова функции `shiftArray(A, 10, 3);` 
Должен получиться массив `{3, 4, 5, 6, 7, 8, 9, 0, 1,2};`

#### Задача 8*.
Заполнить массив nxm (размеры вводит пользователь) числами от 1 до nm зигзагом.

#### Задача 9.
Добавить к функциям из задач 3, 5 и 8 дополнительный аргумент -- направление заполнения.

#### Задача 10.
Выполнить задачи уровня 6kyu из коллекции https://www.codewars.com/collections/tasks-for-basics-of-programming-2021 на языке программирования C++.
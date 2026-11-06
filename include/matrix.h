#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Структура для хранения матрицы.
 */
struct Matrix {
    double** data;
    int rows;
    int cols;
};

/**
 * @brief Создаёт матрицу заданного размера.
 * @param rows Положительное количество строк.
 * @param cols Положительное количество столбцов.
 * @return Новая матрица, заполненная нулями; память освобождается через free_matrix.
 * @exception std::invalid_argument Если rows или cols не положительны.
 * @exception std::bad_alloc Если не удалось выделить память.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождает память, выделенную для матрицы.
 * @param matrix Матрица, полученная из create_matrix или операции над матрицами.
 * @return Ничего не возвращает.
 * @note При data == nullptr ничего не делает, исключений не выбрасывает.
 * Матрица передаётся по значению: после освобождения исходный объект и его копии
 * содержат недействительный указатель, повторно освобождать их нельзя.
 */
void free_matrix(Matrix matrix);

/**
 * @brief Складывает две матрицы.
 * @param first_matrix Первая матрица с выделенными строками данных.
 * @param second_matrix Вторая матрица с выделенными строками данных.
 * @return Новая матрица с суммой; память освобождается через free_matrix.
 * @exception std::invalid_argument Если размеры не совпадают, не положительны
 * или один из указателей data равен nullptr.
 * @exception std::bad_alloc Если не удалось выделить память для результата.
 */
Matrix add_matrices(Matrix first_matrix, Matrix second_matrix);

/**
 * @brief Умножает две матрицы.
 * @param first_matrix Первая матрица с положительными размерами и выделенными строками.
 * @param second_matrix Вторая матрица с положительными размерами и выделенными строками.
 * @return Новая матрица с произведением; память освобождается через free_matrix.
 * @exception std::invalid_argument Если число столбцов первой матрицы не равно
 * числу строк второй, один из data равен nullptr или размеры результата не положительны.
 * @exception std::bad_alloc Если не удалось выделить память для результата.
 */
Matrix multiply_matrices(Matrix first_matrix, Matrix second_matrix);

/**
 * @brief Выводит матрицу в консоль.
 * @param matrix Матрица для вывода с выделенными строками данных.
 * @return Ничего не возвращает.
 * @note При data == nullptr или неположительных размерах выводит [Empty matrix].
 * Большие матрицы выводятся в сокращённом виде.
 * @exception std::ios_base::failure При ошибке вывода, если для std::cout включены исключения.
 */
void print_matrix(Matrix matrix);

/**
 * @brief Транспонирует матрицу.
 * @param matrix Исходная матрица с выделенными строками данных.
 * @return Новая транспонированная матрица; память освобождается через free_matrix.
 * @exception std::invalid_argument Если data равен nullptr или размеры не положительны.
 * @exception std::bad_alloc Если не удалось выделить память для результата.
 */
Matrix transpose_matrix(Matrix matrix);

#endif

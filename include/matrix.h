#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Структура для хранения матрицы.
 */
typedef struct {
    double** data;
    int rows;
    int cols;
} Matrix;

/**
 * @brief Создаёт матрицу заданного размера.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Новая матрица, заполненная нулями.
 * @exception std::invalid_argument Если размеры некорректны.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождает память, выделенную для матрицы.
 * @param m Матрица, память которой необходимо освободить.
 */
void free_matrix(Matrix m);

/**
 * @brief Складывает две матрицы.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица с результатом сложения.
 * @exception std::invalid_argument Если размеры матриц не совпадают.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножает две матрицы.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица с результатом умножения.
 * @exception std::invalid_argument Если размеры матриц несовместимы.
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Выводит матрицу в консоль.
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m);

/**
 * @brief Транспонирует матрицу.
 * @param m Исходная матрица.
 * @return Новая транспонированная матрица.
 * @exception std::invalid_argument Если указатель на данные равен nullptr.
 */
Matrix matrix_transpose(Matrix m);

#endif

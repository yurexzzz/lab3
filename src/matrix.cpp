#include "matrix.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>

namespace {
inline constexpr int kOutputPrecision = 2;
inline constexpr int kMaxRowsToShow = 10;
inline constexpr int kMaxColsToShow = 8;
inline constexpr int kElementWidth = 6;
inline constexpr int kSummaryMarkerCount = 2;
} // namespace

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }

    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;

    matrix.data = new double*[rows];
    if (matrix.data == nullptr) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < rows; i++) {
        matrix.data[i] = new double[cols];
        if (matrix.data[i] == nullptr) {
            for (int j = 0; j < i; j++) {
                delete[] matrix.data[j];
            }
            delete[] matrix.data;
            throw std::bad_alloc();
        }

        for (int j = 0; j < cols; j++) {
            matrix.data[i][j] = 0.0;
        }
    }

    return matrix;
}

void free_matrix(Matrix matrix) {
    if (matrix.data == nullptr) {
        return;
    }

    // Освобождаем память каждой строки.
    for (int i = 0; i < matrix.rows; i++) {
        if (matrix.data[i] != nullptr) {
            delete[] matrix.data[i];
            matrix.data[i] = nullptr;
        }
    }

    delete[] matrix.data;

    matrix.data = nullptr;
    matrix.rows = 0;
    matrix.cols = 0;
}

Matrix add_matrices(Matrix first_matrix, Matrix second_matrix) {
    if (first_matrix.rows != second_matrix.rows || first_matrix.cols != second_matrix.cols) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    if (first_matrix.data == nullptr || second_matrix.data == nullptr) {
        throw std::invalid_argument("Matrix data is null");
    }

    Matrix result = create_matrix(first_matrix.rows, first_matrix.cols);

    for (int i = 0; i < first_matrix.rows; i++) {
        for (int j = 0; j < first_matrix.cols; j++) {
            result.data[i][j] = first_matrix.data[i][j] + second_matrix.data[i][j];
        }
    }

    return result;
}

Matrix multiply_matrices(Matrix first_matrix, Matrix second_matrix) {
    if (first_matrix.cols != second_matrix.rows) {
        throw std::invalid_argument("Matrix dimensions are incompatible");
    }

    if (first_matrix.data == nullptr || second_matrix.data == nullptr) {
        throw std::invalid_argument("Matrix data is null");
    }

    Matrix result = create_matrix(first_matrix.rows, second_matrix.cols);

    for (int i = 0; i < first_matrix.rows; i++) {
        for (int j = 0; j < second_matrix.cols; j++) {
            for (int k = 0; k < first_matrix.cols; k++) {
                result.data[i][j] += first_matrix.data[i][k] * second_matrix.data[k][j];
            }
        }
    }

    return result;
}

void print_matrix(Matrix matrix) {
    // Для пустой матрицы выводим отдельное сообщение.
    if (matrix.data == nullptr || matrix.rows <= 0 || matrix.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(kOutputPrecision);

    const bool show_summary = (matrix.rows > kMaxRowsToShow || matrix.cols > kMaxColsToShow);
    const int rows_to_show = show_summary ? kMaxRowsToShow : matrix.rows;
    const int cols_to_show = show_summary ? kMaxColsToShow : matrix.cols;

    for (int i = 0; i < rows_to_show; i++) {
        if (show_summary && i == kMaxRowsToShow / kSummaryMarkerCount &&
            matrix.rows > kMaxRowsToShow) {
            std::cout << "[...";
            for (int j = 0; j < cols_to_show - kSummaryMarkerCount; j++) {
                std::cout << "       ";
            }
            std::cout << "...]" << std::endl;
            continue;
        }

        std::cout << "[";

        for (int j = 0; j < cols_to_show; j++) {
            if (show_summary && j == kMaxColsToShow / kSummaryMarkerCount &&
                matrix.cols > kMaxColsToShow) {
                std::cout << " ... ";
                continue;
            }

            std::cout << std::setw(kElementWidth) << matrix.data[i][j];

            if (j < cols_to_show - 1) {
                std::cout << " ";
            }
        }

        std::cout << "]";

        if (show_summary && matrix.cols > kMaxColsToShow) {
            std::cout << " ...";
        }

        std::cout << std::endl;
    }

    if (show_summary && matrix.rows > kMaxRowsToShow) {
        std::cout << "[...";
        for (int j = 0; j < std::min(cols_to_show, matrix.cols); j++) {
            std::cout << " ... ";
        }
        std::cout << "...]" << std::endl;
    }

    if (show_summary) {
        std::cout << "Matrix " << matrix.rows << "×" << matrix.cols << " (showing first "
                  << rows_to_show << "×" << cols_to_show << ")" << std::endl;
    }
}

Matrix transpose_matrix(Matrix matrix) {
    if (matrix.data == nullptr) {
        throw std::invalid_argument("Matrix data is null");
    }

    Matrix result = create_matrix(matrix.cols, matrix.rows);

    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            result.data[j][i] = matrix.data[i][j];
        }
    }

    return result;
}

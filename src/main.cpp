#include "matrix.h"
#include <cstdio>

namespace {
inline constexpr int kExampleSize = 2;
} // namespace

int main() {
    Matrix first_matrix = create_matrix(kExampleSize, kExampleSize);
    Matrix second_matrix = create_matrix(kExampleSize, kExampleSize);

    // Исходные данные демонстрационного примера.
    first_matrix.data[0][0] = 1;
    first_matrix.data[0][1] = 2;
    first_matrix.data[1][0] = 3;
    first_matrix.data[1][1] = 4;

    second_matrix.data[0][0] = 5;
    second_matrix.data[0][1] = 6;
    second_matrix.data[1][0] = 7;
    second_matrix.data[1][1] = 8;

    Matrix sum = add_matrices(first_matrix, second_matrix);
    Matrix product = multiply_matrices(first_matrix, second_matrix);

    std::printf("Matrix A:\n");
    print_matrix(first_matrix);

    std::printf("Matrix B:\n");
    print_matrix(second_matrix);

    std::printf("Sum A+B:\n");
    print_matrix(sum);

    free_matrix(first_matrix);
    free_matrix(second_matrix);
    free_matrix(sum);
    free_matrix(product);

    return 0;
}

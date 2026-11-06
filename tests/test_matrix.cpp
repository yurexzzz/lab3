#include "matrix.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(MatrixTest, CreateMatrix_NormalCase) {
    Matrix first_matrix = create_matrix(3, 4);

    EXPECT_EQ(first_matrix.rows, 3);
    EXPECT_EQ(first_matrix.cols, 4);
    EXPECT_NE(first_matrix.data, nullptr);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(first_matrix.data[i][j], 0.0);
        }
    }

    free_matrix(first_matrix);
}

TEST(MatrixTest, Addition_NormalCase) {
    Matrix first_matrix = create_matrix(2, 2);
    Matrix second_matrix = create_matrix(2, 2);

    first_matrix.data[0][0] = 1;
    first_matrix.data[0][1] = 2;
    first_matrix.data[1][0] = 3;
    first_matrix.data[1][1] = 4;
    second_matrix.data[0][0] = 5;
    second_matrix.data[0][1] = 6;
    second_matrix.data[1][0] = 7;
    second_matrix.data[1][1] = 8;

    Matrix sum = add_matrices(first_matrix, second_matrix);

    EXPECT_DOUBLE_EQ(sum.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(sum.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(sum.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(sum.data[1][1], 12.0);

    free_matrix(first_matrix);
    free_matrix(second_matrix);
    free_matrix(sum);
}

TEST(MatrixTest, Multiplication_NormalCase) {
    Matrix first_matrix = create_matrix(2, 2);
    Matrix second_matrix = create_matrix(2, 2);

    first_matrix.data[0][0] = 1;
    first_matrix.data[0][1] = 2;
    first_matrix.data[1][0] = 3;
    first_matrix.data[1][1] = 4;
    second_matrix.data[0][0] = 5;
    second_matrix.data[0][1] = 6;
    second_matrix.data[1][0] = 7;
    second_matrix.data[1][1] = 8;

    Matrix product = multiply_matrices(first_matrix, second_matrix);

    EXPECT_DOUBLE_EQ(product.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(product.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(product.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(product.data[1][1], 50.0);

    free_matrix(first_matrix);
    free_matrix(second_matrix);
    free_matrix(product);
}

TEST(MatrixTest, Transpose_NormalCase) {
    Matrix first_matrix = create_matrix(2, 3);

    first_matrix.data[0][0] = 1;
    first_matrix.data[0][1] = 2;
    first_matrix.data[0][2] = 3;
    first_matrix.data[1][0] = 4;
    first_matrix.data[1][1] = 5;
    first_matrix.data[1][2] = 6;

    Matrix transposed_matrix = transpose_matrix(first_matrix);

    EXPECT_EQ(transposed_matrix.rows, 3);
    EXPECT_EQ(transposed_matrix.cols, 2);

    EXPECT_DOUBLE_EQ(transposed_matrix.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(transposed_matrix.data[0][1], 4.0);
    EXPECT_DOUBLE_EQ(transposed_matrix.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(transposed_matrix.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(transposed_matrix.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(transposed_matrix.data[2][1], 6.0);

    free_matrix(first_matrix);
    free_matrix(transposed_matrix);
}

TEST(MatrixTest, FreeMatrix_NormalCase) {
    Matrix first_matrix = create_matrix(3, 3);
    EXPECT_NO_THROW(free_matrix(first_matrix));
}

TEST(MatrixTest, CreateMatrix_MinimumSize) {
    Matrix first_matrix = create_matrix(1, 1);

    EXPECT_EQ(first_matrix.rows, 1);
    EXPECT_EQ(first_matrix.cols, 1);
    EXPECT_DOUBLE_EQ(first_matrix.data[0][0], 0.0);

    free_matrix(first_matrix);
}

TEST(MatrixTest, Multiplication_RowTimesColumn_1x1) {
    Matrix first_matrix = create_matrix(1, 3);
    Matrix second_matrix = create_matrix(3, 1);

    first_matrix.data[0][0] = 1;
    first_matrix.data[0][1] = 2;
    first_matrix.data[0][2] = 3;
    second_matrix.data[0][0] = 4;
    second_matrix.data[1][0] = 5;
    second_matrix.data[2][0] = 6;

    Matrix product = multiply_matrices(first_matrix, second_matrix);

    EXPECT_EQ(product.rows, 1);
    EXPECT_EQ(product.cols, 1);
    EXPECT_DOUBLE_EQ(product.data[0][0], 32.0);

    free_matrix(first_matrix);
    free_matrix(second_matrix);
    free_matrix(product);
}

TEST(MatrixTest, TransposeTwice_ReturnsOriginal) {
    Matrix first_matrix = create_matrix(2, 3);

    first_matrix.data[0][0] = 1;
    first_matrix.data[0][1] = 2;
    first_matrix.data[0][2] = 3;
    first_matrix.data[1][0] = 4;
    first_matrix.data[1][1] = 5;
    first_matrix.data[1][2] = 6;

    Matrix transposed_matrix = transpose_matrix(first_matrix);
    Matrix restored_matrix = transpose_matrix(transposed_matrix);

    EXPECT_EQ(restored_matrix.rows, 2);
    EXPECT_EQ(restored_matrix.cols, 3);

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_DOUBLE_EQ(restored_matrix.data[i][j], first_matrix.data[i][j]);

    free_matrix(first_matrix);
    free_matrix(transposed_matrix);
    free_matrix(restored_matrix);
}

TEST(MatrixTest, CreateMatrix_ZeroRows) {
    EXPECT_THROW(create_matrix(0, 3), std::invalid_argument);
}

TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(create_matrix(3, -1), std::invalid_argument);
}

TEST(MatrixTest, Addition_SizeMismatch) {
    Matrix first_matrix = create_matrix(2, 2);
    Matrix second_matrix = create_matrix(3, 3);

    EXPECT_THROW(add_matrices(first_matrix, second_matrix), std::invalid_argument);

    free_matrix(first_matrix);
    free_matrix(second_matrix);
}

TEST(MatrixTest, Multiplication_SizeMismatch) {
    Matrix first_matrix = create_matrix(2, 3);
    Matrix second_matrix = create_matrix(2, 2);

    EXPECT_THROW(multiply_matrices(first_matrix, second_matrix), std::invalid_argument);

    free_matrix(first_matrix);
    free_matrix(second_matrix);
}

TEST(MatrixTest, FreeMatrix_EmptyIsSafe) {
    Matrix empty{nullptr, 0, 0};

    EXPECT_NO_THROW(free_matrix(empty));
    EXPECT_NO_THROW(free_matrix(empty));
}

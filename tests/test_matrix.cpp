#include <gtest/gtest.h>
#include "matrix.h"
#include <stdexcept>

TEST(MatrixTest, CreateMatrix_NormalCase) {
    Matrix A = create_matrix(3, 4);

    EXPECT_EQ(A.rows, 3);
    EXPECT_EQ(A.cols, 4);
    EXPECT_NE(A.data, nullptr);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(A.data[i][j], 0.0);
        }
    }

    free_matrix(A);
}

TEST(MatrixTest, Addition_NormalCase) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_add(A, B);

    EXPECT_DOUBLE_EQ(C.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 12.0);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

TEST(MatrixTest, Multiplication_NormalCase) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_multiply(A, B);

    EXPECT_DOUBLE_EQ(C.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 50.0);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

TEST(MatrixTest, Transpose_NormalCase) {
    Matrix A = create_matrix(2, 3);

    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    Matrix T = matrix_transpose(A);

    EXPECT_EQ(T.rows, 3);
    EXPECT_EQ(T.cols, 2);

    EXPECT_DOUBLE_EQ(T.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(T.data[0][1], 4.0);
    EXPECT_DOUBLE_EQ(T.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(T.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(T.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(T.data[2][1], 6.0);

    free_matrix(A);
    free_matrix(T);
}

TEST(MatrixTest, FreeMatrix_NormalCase) {
    Matrix A = create_matrix(3, 3);
    EXPECT_NO_THROW(free_matrix(A));
}

TEST(MatrixTest, CreateMatrix_MinimumSize) {
    Matrix A = create_matrix(1, 1);

    EXPECT_EQ(A.rows, 1);
    EXPECT_EQ(A.cols, 1);
    EXPECT_DOUBLE_EQ(A.data[0][0], 0.0);

    free_matrix(A);
}

TEST(MatrixTest, Multiplication_RowTimesColumn_1x1) {
    Matrix A = create_matrix(1, 3);
    Matrix B = create_matrix(3, 1);

    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    B.data[0][0] = 4;
    B.data[1][0] = 5;
    B.data[2][0] = 6;

    Matrix C = matrix_multiply(A, B);

    EXPECT_EQ(C.rows, 1);
    EXPECT_EQ(C.cols, 1);
    EXPECT_DOUBLE_EQ(C.data[0][0], 32.0);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

TEST(MatrixTest, TransposeTwice_ReturnsOriginal) {
    Matrix A = create_matrix(2, 3);

    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    Matrix T = matrix_transpose(A);
    Matrix TT = matrix_transpose(T);

    EXPECT_EQ(TT.rows, 2);
    EXPECT_EQ(TT.cols, 3);

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_DOUBLE_EQ(TT.data[i][j], A.data[i][j]);

    free_matrix(A);
    free_matrix(T);
    free_matrix(TT);
}

TEST(MatrixTest, CreateMatrix_ZeroRows) {
    EXPECT_THROW(create_matrix(0, 3), std::invalid_argument);
}

TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(create_matrix(3, -1), std::invalid_argument);
}

TEST(MatrixTest, Addition_SizeMismatch) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 3);

    EXPECT_THROW(matrix_add(A, B), std::invalid_argument);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixTest, Multiplication_SizeMismatch) {
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(2, 2);

    EXPECT_THROW(matrix_multiply(A, B), std::invalid_argument);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixTest, FreeMatrix_EmptyIsSafe) {
    Matrix empty{nullptr, 0, 0};

    EXPECT_NO_THROW(free_matrix(empty));
    EXPECT_NO_THROW(free_matrix(empty));
}

//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     RICHARD KOCIAN <xkocia19@stud.fit.vutbr.cz>
// $Date:       $2022-03-10
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author RICHARD KOCIAN
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

class Matrix_1x1 : public ::testing::Test {
protected:

    Matrix *matrix_1;
    Matrix *matrix_2;
    Matrix *matrix_3;

    virtual void SetUp() {
        matrix_1 = new Matrix();
        matrix_2 = new Matrix();
        matrix_3 = new Matrix();
        matrix_3->set({{2}});

    }

    virtual void TearDown() {
        delete matrix_1;
        delete matrix_2;
        delete matrix_3;
    }
};

TEST_F(Matrix_1x1, Constructor) {
    EXPECT_NO_THROW(*matrix_1 = Matrix());
    EXPECT_NO_THROW(*matrix_1 = Matrix(1,1));
}

TEST_F(Matrix_1x1, Constructor_err) {
    EXPECT_ANY_THROW(*matrix_1 = Matrix(0, 0));
    EXPECT_ANY_THROW(*matrix_1 = Matrix(-1, 3));
    EXPECT_ANY_THROW(*matrix_1 = Matrix(1, -3));
}

TEST_F(Matrix_1x1, Set) {
    ASSERT_TRUE(matrix_1->set(0, 0, 1));
    EXPECT_EQ(matrix_1->get(0, 0), 1);
}

TEST_F(Matrix_1x1, Set_err) {
    EXPECT_FALSE(matrix_1->set(-1, 0, 1));
    EXPECT_FALSE(matrix_1->set(0, -5, -5));
    EXPECT_FALSE(matrix_1->set(1, 0, 4));
    EXPECT_FALSE(matrix_1->set(0, 1, 4));
}

TEST_F(Matrix_1x1, Set_ViaValues) {
    EXPECT_TRUE(matrix_1->set({{1}}));
}

TEST_F(Matrix_1x1, Set_ViaValues_err) {
    EXPECT_FALSE(matrix_1->set({{1},{1}}));
}

TEST_F(Matrix_1x1, Get) {
    EXPECT_NO_THROW(matrix_1->get(0, 0));
    EXPECT_EQ(matrix_1->get(0, 0), 0);
}

TEST_F(Matrix_1x1, Get_err) {
    EXPECT_ANY_THROW(matrix_1->get(0, 1));
    EXPECT_ANY_THROW(matrix_1->get(1, 0));
    EXPECT_ANY_THROW(matrix_1->get(1, 1));

    EXPECT_ANY_THROW(matrix_1->get(0, -1));
    EXPECT_ANY_THROW(matrix_1->get(-1, 0));
    EXPECT_ANY_THROW(matrix_1->get(-1, -1));

    EXPECT_ANY_THROW(matrix_1->get(10000, 5000));
}

TEST_F(Matrix_1x1, OperatorEquals) {
    Matrix emptyMatrix2 = Matrix();
    EXPECT_TRUE(matrix_1->operator==(emptyMatrix2));

    Matrix emptyMatrix3 = Matrix();
    emptyMatrix3.set(0, 0, 1);
    EXPECT_FALSE(matrix_1->operator==(emptyMatrix3));

    Matrix nonEmptyMatrix = Matrix();
    nonEmptyMatrix.set({{2}});
    EXPECT_TRUE(matrix_3->operator==(nonEmptyMatrix));
}

TEST_F(Matrix_1x1, OperatorEquals_err) {
    Matrix emptyMatrix = Matrix(1, 2);
    EXPECT_ANY_THROW(matrix_1->operator==(emptyMatrix));
}

TEST_F(Matrix_1x1, OperatorPlus) {
    Matrix emptyMatrix2 = Matrix();
    EXPECT_NO_THROW(matrix_1->operator+(emptyMatrix2));
}

TEST_F(Matrix_1x1, OperatorPlus_Result) {
    Matrix emptyMatrix2 = Matrix();
    EXPECT_EQ(matrix_1->operator+(emptyMatrix2), emptyMatrix2);
}

TEST_F(Matrix_1x1, OperatorPlus_err) {
    Matrix emptyMatrix_2_1 = Matrix(2, 1);
    EXPECT_ANY_THROW(matrix_1->operator+(emptyMatrix_2_1));
}

TEST_F(Matrix_1x1, OperatorMultiply_Matrix) {
    Matrix emptyMatrix2 = Matrix();
    EXPECT_NO_THROW(matrix_1->operator*(emptyMatrix2));
}

TEST_F(Matrix_1x1, OperatorMultiply_Matrix_result) {
    Matrix emptyMatrix2 = Matrix();
    EXPECT_EQ(matrix_1->operator*(emptyMatrix2), emptyMatrix2);
}

TEST_F(Matrix_1x1, OperatorMultiply_Matrix_err) {
    Matrix emptyMatrix_2_2 = Matrix(2, 2);
    EXPECT_ANY_THROW(matrix_1->operator*(emptyMatrix_2_2));
}

TEST_F(Matrix_1x1, OpeatorMultiply_Scalar) {
    EXPECT_NO_THROW(matrix_1->operator*(4));
}

TEST_F(Matrix_1x1, OpeatorMultiply_Scalar_result) {
    Matrix emptyMatrix2 = Matrix();
    EXPECT_EQ(matrix_1->operator*(-5), emptyMatrix2);
}

TEST_F(Matrix_1x1, SolveEqation) {
    matrix_1->set(0,0,1);
    EXPECT_NO_THROW(matrix_1->solveEquation({1}));
}

TEST_F(Matrix_1x1, SolveEqation_err) {
    EXPECT_ANY_THROW(matrix_1->solveEquation({1}));
}

TEST_F(Matrix_1x1, Transpose) {
    EXPECT_NO_THROW(matrix_1->transpose());
}

TEST_F(Matrix_1x1, Transpose_result) {
    Matrix emptyMatrix2 = Matrix();
    EXPECT_EQ(matrix_1->transpose(), emptyMatrix2);
}

TEST_F(Matrix_1x1, Inverse) {
    EXPECT_ANY_THROW(matrix_1->inverse());
}

class Matrix_2x2 : public ::testing::Test {
protected:
    Matrix *matrix1;
    Matrix *matrix2;

    virtual void SetUp() {
        matrix1 = new Matrix(2, 2);
        std::vector<std::vector<double> > values = { {1,2},
                                                     {3,4} };
        matrix1->set(values);
        matrix2 = new Matrix(2, 2);
        std::vector<std::vector<double> > values2 = { {1,2},
                                                     {3,4} };
        matrix2->set(values);
    }

    virtual void TearDown() {
        delete matrix1;
        delete matrix2;
    }
};

TEST_F(Matrix_2x2, Set) {
    ASSERT_TRUE(matrix1->set(1, 1, 5));
    EXPECT_EQ(matrix1->get(1, 1), 5);
}

TEST_F(Matrix_2x2, Set_err) {
    EXPECT_FALSE(matrix1->set(3, 0, 1));
    EXPECT_FALSE(matrix1->set(0, -5, -5));
}

TEST_F(Matrix_2x2, Set_ViaValues) {
    EXPECT_TRUE(matrix1->set({{1, 2}, {3, 4}}));
}

TEST_F(Matrix_2x2, Set_ViaValues_err) {
    EXPECT_FALSE(matrix1->set({{1}, {1}}));
}

TEST_F(Matrix_2x2, Get) {
    EXPECT_NO_THROW(matrix1->get(0, 0));
    EXPECT_EQ(matrix1->get(0, 0), 1);

    EXPECT_NO_THROW(matrix1->get(1, 0));
    EXPECT_EQ(matrix1->get(1, 0), 3);
}

TEST_F(Matrix_2x2, Get_err) {

    EXPECT_ANY_THROW(matrix1->get(0, -1));
    EXPECT_ANY_THROW(matrix1->get(-1, 0));
    EXPECT_ANY_THROW(matrix1->get(-1, -1));

    EXPECT_ANY_THROW(matrix1->get(10000, 5000));
}

TEST_F(Matrix_2x2, OperatorEquals) {
    Matrix matrix_2x2_2 = Matrix(2,2);
    matrix_2x2_2.set({ {1,2},
                       {3,4} });
    EXPECT_TRUE(matrix1->operator==(matrix_2x2_2));

    matrix_2x2_2.set(0,0,2);

    EXPECT_FALSE(matrix1->operator==(matrix_2x2_2));
}

TEST_F(Matrix_2x2, OperatorEquals_err) {
    Matrix emptyMatrix = Matrix(1, 2);
    EXPECT_ANY_THROW(matrix1->operator==(emptyMatrix));
}

TEST_F(Matrix_2x2, OperatorPlus) {
    Matrix emptyMatrix2 = Matrix(2,2);
    EXPECT_NO_THROW(matrix1->operator+(emptyMatrix2));
}

TEST_F(Matrix_2x2, OperatorPlus_Result) {
    Matrix emptyMatrix2 = Matrix(2,2);
    EXPECT_EQ(matrix1->operator+(emptyMatrix2), *matrix2);

    Matrix matrix3 = Matrix(2,2);
    matrix3.set( { {2,4},
                   {6,8} });

    EXPECT_EQ(matrix1->operator+(*matrix2), matrix3);
}

TEST_F(Matrix_2x2, OperatorPlus_err) {
    Matrix emptyMatrix_2_1 = Matrix(2, 1);
    EXPECT_ANY_THROW(matrix1->operator+(emptyMatrix_2_1));
}

TEST_F(Matrix_2x2, OperatorMultiply_Matrix) {
    Matrix emptyMatrix2 = Matrix(2,2);
    emptyMatrix2.set({{0,0},{0,0}});
    EXPECT_NO_THROW(matrix1->operator*(emptyMatrix2));
}

TEST_F(Matrix_2x2, OperatorMultiply_Matrix_result) {
    Matrix matrix3 = Matrix(2,2);
    matrix3.set({{1,1},{1,1}});
    ASSERT_NO_THROW(matrix2->operator*(matrix3));
    EXPECT_EQ(matrix2->operator*(matrix3).get(0,0),3);

    Matrix emptyMatrix2 = Matrix(2,2);
    EXPECT_EQ(matrix1->operator*(emptyMatrix2), emptyMatrix2);
}

TEST_F(Matrix_2x2, OperatorMultiply_Matrix_err) {
    Matrix emptyMatrix_3_3 = Matrix(3, 3);
    EXPECT_ANY_THROW(matrix1->operator*(emptyMatrix_3_3));
}

TEST_F(Matrix_2x2, OpeatorMultiply_Scalar) {
    EXPECT_NO_THROW(matrix2->operator*(4));
}

TEST_F(Matrix_2x2, OpeatorMultiply_Scalar_result) {
    EXPECT_EQ(matrix1->operator*(1), *matrix2);
}

TEST_F(Matrix_2x2, SolveEqation) {
    EXPECT_NO_THROW(matrix1->solveEquation({1,2}));
}

TEST_F(Matrix_2x2, SolveEqation_err) {
    EXPECT_ANY_THROW(matrix1->solveEquation({1}));
}

TEST_F(Matrix_2x2, Transpose) {
    EXPECT_NO_THROW(matrix1->transpose());
}

TEST_F(Matrix_2x2, Transpose_result) {
    Matrix matrix3 = Matrix(2,2);
    matrix3.set({{1,3}, {2,4}});
    EXPECT_EQ(matrix1->transpose(), matrix3);
}

TEST_F(Matrix_2x2, Inverse) {
    EXPECT_NO_THROW(matrix1->inverse());
}

class Matrix_2x1 : public ::testing::Test {
protected:
    Matrix *matrix1;
    Matrix *matrix2;

    virtual void SetUp() {
        matrix1 = new Matrix(2, 1);
        std::vector<std::vector<double> > values = { {1},
                                                     {3} };
        matrix1->set(values);

        matrix2 = new Matrix(2, 1);
        std::vector<std::vector<double> > values2 = { {1},
                                                     {3} };
        matrix2->set(values2);
    }

    virtual void TearDown() {
        delete matrix1;
        delete matrix2;
    }
};

TEST_F(Matrix_2x1, Set) {
    ASSERT_TRUE(matrix1->set(0, 0, 5));
    EXPECT_EQ(matrix1->get(0, 0), 5);
}

TEST_F(Matrix_2x1, Set_err) {
    EXPECT_FALSE(matrix1->set(3, 0, 1));
    EXPECT_FALSE(matrix1->set(0, -5, -5));
}

TEST_F(Matrix_2x1, Set_ViaValues) {
    EXPECT_TRUE(matrix1->set({{1}, {2}}));
}

TEST_F(Matrix_2x1, Set_ViaValues_err) {
    EXPECT_FALSE(matrix1->set({{1,3}, {1}}));
}

TEST_F(Matrix_2x1, Get) {
    EXPECT_NO_THROW(matrix1->get(0, 0));
    EXPECT_EQ(matrix1->get(0, 0), 1);

    EXPECT_NO_THROW(matrix1->get(1, 0));
    EXPECT_EQ(matrix1->get(1, 0), 3);
}

TEST_F(Matrix_2x1, Get_err) {

    EXPECT_ANY_THROW(matrix1->get(0, -1));
    EXPECT_ANY_THROW(matrix1->get(-1, 0));
    EXPECT_ANY_THROW(matrix1->get(-1, -1));

    EXPECT_ANY_THROW(matrix1->get(10000, 5000));
}

TEST_F(Matrix_2x1, OperatorEquals) {
    Matrix matrix_2x1_2 = Matrix(2,1);
    matrix_2x1_2.set({ {1},
                       {3} });
    EXPECT_TRUE(matrix1->operator==(matrix_2x1_2));

    matrix_2x1_2.set(0,0,2);

    EXPECT_FALSE(matrix1->operator==(matrix_2x1_2));
}

TEST_F(Matrix_2x1, OperatorEquals_err) {
    Matrix emptyMatrix = Matrix(4, 2);
    EXPECT_ANY_THROW(matrix1->operator==(emptyMatrix));
}

TEST_F(Matrix_2x1, OperatorPlus) {
    Matrix emptyMatrix2 = Matrix(2,1);
    EXPECT_NO_THROW(matrix1->operator+(emptyMatrix2));
}

TEST_F(Matrix_2x1, OperatorPlus_Result) {
    Matrix emptyMatrix2 = Matrix(2,1);
    EXPECT_EQ(matrix1->operator+(emptyMatrix2), *matrix2);

    Matrix matrix3 = Matrix(2,1);
    matrix3.set( { {2},
                   {6} });

    EXPECT_EQ(matrix1->operator+(*matrix2), matrix3);
}

TEST_F(Matrix_2x1, OperatorPlus_err) {
    Matrix emptyMatrix_2_1 = Matrix(4, 1);
    EXPECT_ANY_THROW(matrix1->operator+(emptyMatrix_2_1));
}

TEST_F(Matrix_2x1, OperatorMultiply_Matrix) {
    Matrix emptyMatrix2 = Matrix(1,2);
    EXPECT_NO_THROW(matrix1->operator*(emptyMatrix2));
}

TEST_F(Matrix_2x1, OperatorMultiply_Matrix_result) {
    Matrix matrix3 = Matrix(1,2);
    matrix3.set({{1,1}});
    ASSERT_NO_THROW(matrix2->operator*(matrix3));
    EXPECT_EQ(matrix2->operator*(matrix3).get(0,0),1);

    Matrix emptyMatrix2 = Matrix(1,2);
    EXPECT_EQ(matrix1->operator*(emptyMatrix2).get(0,0), emptyMatrix2.get(0,0));
}

TEST_F(Matrix_2x1, OperatorMultiply_Matrix_err) {
    Matrix emptyMatrix_3_3 = Matrix(3, 3);
    EXPECT_ANY_THROW(matrix1->operator*(emptyMatrix_3_3));
}

TEST_F(Matrix_2x1, OpeatorMultiply_Scalar) {
    EXPECT_NO_THROW(matrix2->operator*(4));
}

TEST_F(Matrix_2x1, OpeatorMultiply_Scalar_result) {
    EXPECT_EQ(matrix1->operator*(1),*matrix2);
}

TEST_F(Matrix_2x1, SolveEqation_err) {
    EXPECT_ANY_THROW(matrix1->solveEquation({1}));
}

TEST_F(Matrix_2x1, Transpose) {
    EXPECT_NO_THROW(matrix1->transpose());
}

TEST_F(Matrix_2x1, Transpose_result) {
    Matrix matrix3 = Matrix(1,2);
    matrix3.set({{1,3}});
    EXPECT_EQ(matrix1->transpose(), matrix3);
}

TEST_F(Matrix_2x1, Inverse) {
    EXPECT_ANY_THROW(matrix1->inverse());
}

class Matrix_3x3 : public ::testing::Test {
protected:
    Matrix *matrix1;
    Matrix *matrix2;
    Matrix *matrix3;

    virtual void SetUp() {
        matrix1 = new Matrix(3, 3);
        std::vector<std::vector<double> > values = { {1,2,3},
                                                     {4,5,6},
                                                     {7,8,9}};
        matrix1->set(values);
        matrix2 = new Matrix(3, 3);
        std::vector<std::vector<double> > values2 = { {1,2,3},
                                                      {4,5,6},
                                                      {7,8,9}};
        matrix2->set(values);

        matrix3 = new Matrix(3,3);

        std::vector<std::vector<double> > values3 = { {1,2,3},
                                                      {1,1,5},
                                                      {2,2,2}};
        matrix3->set(values3);
    }

    virtual void TearDown() {
        delete matrix1;
        delete matrix2;
        delete matrix3;
    }
};

TEST_F(Matrix_3x3, Set) {
    ASSERT_TRUE(matrix1->set(1, 1, 5));
    EXPECT_EQ(matrix1->get(1, 1), 5);
}

TEST_F(Matrix_3x3, Set_err) {
    EXPECT_FALSE(matrix1->set(4, 0, 1));
    EXPECT_FALSE(matrix1->set(0, -5, -5));
}

TEST_F(Matrix_3x3, Set_ViaValues) {
    EXPECT_TRUE(matrix1->set({{1,3,4}, {3,4,5},{1,2,3}}));
}

TEST_F(Matrix_3x3, Set_ViaValues_err) {
    EXPECT_FALSE(matrix1->set({{1}, {1}, {1}}));
}

TEST_F(Matrix_3x3, Get) {
    EXPECT_NO_THROW(matrix1->get(0, 0));
    EXPECT_EQ(matrix1->get(0, 0), 1);

    EXPECT_NO_THROW(matrix1->get(2, 0));
    EXPECT_EQ(matrix1->get(2, 0), 7);
}

TEST_F(Matrix_3x3, Get_err) {

    EXPECT_ANY_THROW(matrix1->get(0, -1));
    EXPECT_ANY_THROW(matrix1->get(-1, 0));
    EXPECT_ANY_THROW(matrix1->get(-1, -1));

    EXPECT_ANY_THROW(matrix1->get(10000, 5000));
}

TEST_F(Matrix_3x3, OperatorEquals) {
    Matrix matrix_3x3_2 = Matrix(3,3);
    matrix_3x3_2.set({ {1,2,3},
                       {4,5,6}, {7,8,9} });
    EXPECT_TRUE(matrix1->operator==(matrix_3x3_2));
    matrix_3x3_2.set(2,0,9);
    EXPECT_FALSE(matrix1->operator==(matrix_3x3_2));
}

TEST_F(Matrix_3x3, OperatorEquals_err) {
    Matrix emptyMatrix = Matrix(1, 2);
    EXPECT_ANY_THROW(matrix1->operator==(emptyMatrix));
}

TEST_F(Matrix_3x3, OperatorPlus) {
    Matrix emptyMatrix2 = Matrix(3,3);
    EXPECT_NO_THROW(matrix1->operator+(emptyMatrix2));
}

TEST_F(Matrix_3x3, OperatorPlus_Result) {
    Matrix emptyMatrix2 = Matrix(3,3);
    EXPECT_EQ(matrix1->operator+(emptyMatrix2), *matrix2);

    Matrix matrix3 = Matrix(3,3);
    matrix3.set( { {2,4,6},
                   {8,10,12},{14,16,18} });

    EXPECT_EQ(matrix1->operator+(*matrix2), matrix3);
}

TEST_F(Matrix_3x3, OperatorPlus_err) {
    Matrix emptyMatrix_2_1 = Matrix(2, 1);
    EXPECT_ANY_THROW(matrix1->operator+(emptyMatrix_2_1));
}

TEST_F(Matrix_3x3, OperatorMultiply_Matrix) {
    Matrix emptyMatrix2 = Matrix(3,3);
    EXPECT_NO_THROW(matrix1->operator*(emptyMatrix2));
}

TEST_F(Matrix_3x3, OperatorMultiply_Matrix_result) {
    Matrix matrix3 = Matrix(3,3);
    matrix3.set({{1,1,1},{1,1,1},{1,1,1}});
    ASSERT_NO_THROW(matrix2->operator*(matrix3));
    EXPECT_EQ(matrix2->operator*(matrix3).get(0,0),6);

    Matrix emptyMatrix2 = Matrix(3,3);
    EXPECT_EQ(matrix1->operator*(emptyMatrix2), emptyMatrix2);
}

TEST_F(Matrix_3x3, OperatorMultiply_Matrix_err) {
    Matrix emptyMatrix_3_3 = Matrix(4, 3);
    EXPECT_ANY_THROW(matrix1->operator*(emptyMatrix_3_3));
}

TEST_F(Matrix_3x3, OpeatorMultiply_Scalar) {
    EXPECT_NO_THROW(matrix2->operator*(4));
}

TEST_F(Matrix_3x3, OpeatorMultiply_Scalar_result) {
    EXPECT_EQ(matrix1->operator*(1), *matrix2);
}

TEST_F(Matrix_3x3, SolveEqation_err) {
    EXPECT_ANY_THROW(matrix1->solveEquation({1}));
    EXPECT_ANY_THROW(matrix1->solveEquation({1,2,3}));
}

TEST_F(Matrix_3x3, Transpose) {
    EXPECT_NO_THROW(matrix1->transpose());
}
TEST_F(Matrix_3x3, Transpose_result) {
    Matrix matrix3 = Matrix(3,3);
    matrix3.set({{1, 4, 7},
                 {2, 5, 8,},
                 {3, 6, 9}});
    EXPECT_EQ(matrix1->transpose(), matrix3);
}

TEST_F(Matrix_3x3, Inverse) {
    EXPECT_NO_THROW(matrix3->inverse());
}

TEST_F(Matrix_3x3, Inverse_err) {
    EXPECT_ANY_THROW(matrix1->inverse());
}

class Matrix_4x4 : public ::testing::Test {
protected:
    Matrix *matrix1;
    Matrix *matrix2;

    virtual void SetUp() {
        matrix1 = new Matrix(4, 4);
        std::vector<std::vector<double> > values = { {1,2,3,4},
                                                     {5,6,7,8},
                                                     {9,10,11,12},
                                                     {13,14,15,16}};
        matrix1->set(values);
        matrix2 = new Matrix(4, 4);
        std::vector<std::vector<double> > values2 = { {1,2,3,4},
                                                     {5,6,7,8},
                                                     {9,10,11,12},
                                                     {13,14,15,16}};
        matrix2->set(values);
    }

    virtual void TearDown() {
        delete matrix1;
        delete matrix2;
    }
};

TEST_F(Matrix_4x4, Set) {
    ASSERT_TRUE(matrix1->set(1, 1, 5));
    EXPECT_EQ(matrix1->get(1, 1), 5);
}

TEST_F(Matrix_4x4, Set_err) {
    EXPECT_FALSE(matrix1->set(4, 0, 1));
    EXPECT_FALSE(matrix1->set(0, -5, -5));
}

TEST_F(Matrix_4x4, Set_ViaValues) {
    EXPECT_TRUE(matrix1->set({{1,3,4,5}, {3,4,5,5},{1,2,3,8},{2,9,7,2}}));
}

TEST_F(Matrix_4x4, Set_ViaValues_err) {
    EXPECT_FALSE(matrix1->set({{1}, {1}, {1}}));
}

TEST_F(Matrix_4x4, Get) {
    EXPECT_NO_THROW(matrix1->get(0, 0));
    EXPECT_EQ(matrix1->get(0, 0), 1);

    EXPECT_NO_THROW(matrix1->get(2, 0));
    EXPECT_EQ(matrix1->get(3, 3), 16);
}

TEST_F(Matrix_4x4, Get_err) {

    EXPECT_ANY_THROW(matrix1->get(0, -1));
    EXPECT_ANY_THROW(matrix1->get(-1, 0));
    EXPECT_ANY_THROW(matrix1->get(-1, -1));

    EXPECT_ANY_THROW(matrix1->get(10000, 5000));
}

TEST_F(Matrix_4x4, OperatorEquals) {
    Matrix matrix_4x4_2 = Matrix(4,4);
    matrix_4x4_2.set({ {1,2,3,4},
                       {5,6,7,8}, {9,10,11,12},{13,14,15,16} });
    EXPECT_TRUE(matrix1->operator==(matrix_4x4_2));
    matrix_4x4_2.set(3,3,5);
    EXPECT_FALSE(matrix1->operator==(matrix_4x4_2));
}

TEST_F(Matrix_4x4, OperatorEquals_err) {
    Matrix emptyMatrix = Matrix(1, 2);
    EXPECT_ANY_THROW(matrix1->operator==(emptyMatrix));
}

TEST_F(Matrix_4x4, OperatorPlus) {
    Matrix emptyMatrix2 = Matrix(4,4);
    EXPECT_NO_THROW(matrix1->operator+(emptyMatrix2));
}

TEST_F(Matrix_4x4, OperatorPlus_Result) {
    Matrix emptyMatrix2 = Matrix(4,4);
    EXPECT_EQ(matrix1->operator+(emptyMatrix2), *matrix2);

    Matrix matrix3 = Matrix(4,4);
    matrix3.set( { {2,4,6,8},
                   {10,12,14,16}, {18,20,22,24},{26,28,30,32} });

    EXPECT_EQ(matrix1->operator+(*matrix2), matrix3);
}

TEST_F(Matrix_4x4, OperatorPlus_err) {
    Matrix emptyMatrix_2_1 = Matrix(2, 1);
    EXPECT_ANY_THROW(matrix1->operator+(emptyMatrix_2_1));
}

TEST_F(Matrix_4x4, OperatorMultiply_Matrix) {
    Matrix emptyMatrix2 = Matrix(4,4);
    EXPECT_NO_THROW(matrix1->operator*(emptyMatrix2));
}

TEST_F(Matrix_4x4, OperatorMultiply_Matrix_result) {
    Matrix matrix3 = Matrix(4,4);
    matrix3.set({{2,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}});
    ASSERT_NO_THROW(matrix2->operator*(matrix3));
    matrix1->set({ {11,10,10,10},
                   {31,26,26,26}, {51,42,42,42},{71,58,58,58} });
    EXPECT_TRUE(matrix1->operator==(matrix2->operator*(matrix3)));

    Matrix emptyMatrix2 = Matrix(4,4);
    EXPECT_EQ(matrix1->operator*(emptyMatrix2), emptyMatrix2);
}

TEST_F(Matrix_4x4, OperatorMultiply_Matrix_err) {
    Matrix emptyMatrix_3_3 = Matrix(5, 3);
    EXPECT_ANY_THROW(matrix1->operator*(emptyMatrix_3_3));
}

TEST_F(Matrix_4x4, OpeatorMultiply_Scalar) {
    EXPECT_NO_THROW(matrix2->operator*(4));
}

TEST_F(Matrix_4x4, OpeatorMultiply_Scalar_result) {
    EXPECT_EQ(matrix1->operator*(1), *matrix2);
}

TEST_F(Matrix_4x4, SolveEqation_err) {
    EXPECT_ANY_THROW(matrix1->solveEquation({1}));
    EXPECT_ANY_THROW(matrix1->solveEquation({1,2,3}));
}

TEST_F(Matrix_4x4, Transpose) {
    EXPECT_NO_THROW(matrix1->transpose());
}

TEST_F(Matrix_4x4, Transpose_result) {
    Matrix matrix3 = Matrix(4,4);
    matrix3.set({ {1,5,9,13},
                  {2,6,10,14},
                  {3,7,11,15},
                  {4,8,12,16}});
    EXPECT_EQ(matrix1->transpose(), matrix3);
}

TEST_F(Matrix_4x4, Inverse_err) {
    EXPECT_ANY_THROW(matrix1->inverse());
}

TEST_F(Matrix_4x4, SolveEqation) {
    EXPECT_ANY_THROW(matrix1->solveEquation({1,2,3,4}));
}



//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

/*** Konec souboru white_box_tests.cpp ***/

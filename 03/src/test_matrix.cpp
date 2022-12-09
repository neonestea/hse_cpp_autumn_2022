#include <gtest/gtest.h>
#include <iostream>
#include "matrix.cpp"


class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestUtils, check_equal)
{
    Matrix matrixA(3, 2);
    Matrix matrixB(3, 2);
    bool equal = (matrixA == matrixB);
    bool not_equal = (matrixA != matrixB);
    ASSERT_EQ(equal, 1);
    ASSERT_EQ(not_equal, 0);
}

TEST(TestUtils, check_not_equal)
{
    Matrix matrixA(3, 2);
    matrixA.setElement(1, 1, 4);
    Matrix matrixB(3, 2);
    bool equal = (matrixA == matrixB);
    bool not_equal = (matrixA != matrixB);
    ASSERT_EQ(equal, 0);
    ASSERT_EQ(not_equal, 1);
}

TEST(TestUtils, check_element)
{
    Matrix matrixA(3, 2);
    matrixA.setElement(1, 1, 4);
    ASSERT_EQ(4, matrixA.getElement(1, 1));
}

TEST(TestUtils, check_rows_cols)
{
    Matrix matrixA(5, 6);
    ASSERT_EQ(5, matrixA.getRows());
    ASSERT_EQ(6, matrixA.getColumns());
}

TEST(TestUtils, check_sum)
{
    Matrix matrixA(3, 2);
    Matrix matrixB(3, 2);
    Matrix matrixCheck(3, 2);

    matrixA.setElement(0, 0, 5);
    matrixA.setElement(0, 1, 3);
    matrixA.setElement(1, 0, 2);
    matrixA.setElement(1, 1, 6);
    matrixA.setElement(2, 0, 4);
    matrixA.setElement(2, 1, 1);


    matrixB.setElement(0, 0, 4);
    matrixB.setElement(0, 1, 5);
    matrixB.setElement(1, 0, 2);
    matrixB.setElement(1, 1, 2);
    matrixB.setElement(2, 0, 4);
    matrixB.setElement(2, 1, 7);

    Matrix sumMatrix = matrixA + matrixB;

    matrixCheck.setElement(0, 0, 9);
    matrixCheck.setElement(0, 1, 8);
    matrixCheck.setElement(1, 0, 4);
    matrixCheck.setElement(1, 1, 8);
    matrixCheck.setElement(2, 0, 8);
    matrixCheck.setElement(2, 1, 8);


    bool equal = (sumMatrix == matrixCheck);
    ASSERT_EQ(equal, 1);
}

TEST(TestUtils, check_mult)
{
    Matrix matrixA(2, 2);
    matrixA.setElement(0, 0, 1);
    matrixA.setElement(0, 1, 1);
    matrixA.setElement(1, 0, 1);
    matrixA.setElement(1, 1, 1);
    matrixA *= 5;

    Matrix matrixCheck(2, 2);
    matrixCheck.setElement(0, 0, 5);
    matrixCheck.setElement(0, 1, 5);
    matrixCheck.setElement(1, 0, 5);
    matrixCheck.setElement(1, 1, 5);
    bool equal = (matrixA == matrixCheck);
    ASSERT_EQ(equal, 1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
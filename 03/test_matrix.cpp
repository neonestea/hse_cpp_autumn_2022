#include <gtest/gtest.h>
#include <iostream>
#include "matrix.h"


class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestUtils, check_equal)
{
    Matrix matrixA(3, 2);
    matrixA[0][0] = 5;
    matrixA[0][1] = 3;
    matrixA[1][0] = 2;
    matrixA[1][1] = 6;
    matrixA[2][0] = 4;
    matrixA[2][1] = 1;
    Matrix matrixB(3, 2);
    matrixB[0][0] = 5;
    matrixB[0][1] = 3;
    matrixB[1][0] = 2;
    matrixB[1][1] = 6;
    matrixB[2][0] = 4;
    matrixB[2][1] = 1;
    bool equal = (matrixA == matrixB);
    bool not_equal = (matrixA != matrixB);
    ASSERT_EQ(equal, 1);
    ASSERT_EQ(not_equal, 0);
}

TEST(TestUtils, check_not_equal)
{
    Matrix matrixA(3, 2);
    matrixA[0][0] = 5;
    matrixA[0][1] = 3;
    matrixA[1][0] = 2;
    matrixA[1][1] = 6;
    matrixA[2][0] = 4;
    matrixA[2][1] = 1;
    Matrix matrixB(3, 2);
    matrixB[0][0] = 1;
    matrixB[0][1] = 3;
    matrixB[1][0] = 2;
    matrixB[1][1] = 6;
    matrixB[2][0] = 4;
    matrixB[2][1] = 1;
    std::cout << matrixA << std::endl;
    
    bool equal = (matrixA == matrixB);
    bool not_equal = (matrixA != matrixB);
    ASSERT_EQ(equal, 0);
    ASSERT_EQ(not_equal, 1);
}

TEST(TestUtils, check_element)
{
    Matrix matrixA(3, 2);
    matrixA[0][0] = 5;
    matrixA[0][1] = 3;
    matrixA[1][0] = 2;
    matrixA[1][1] = 6;
    matrixA[2][0] = 4;
    matrixA[2][1] = 1;
    
    ASSERT_EQ(5, matrixA[0][0]);
    ASSERT_EQ(3, matrixA[0][1]);
    ASSERT_EQ(2, matrixA[1][0]);
    ASSERT_EQ(6, matrixA[1][1]);
    ASSERT_EQ(4, matrixA[2][0]);
    ASSERT_EQ(1, matrixA[2][1]);
}

TEST(TestUtils, check_rows_cols)
{
    Matrix matrixA(3, 2);
    matrixA[0][0] = 5;
    matrixA[0][1] = 3;
    matrixA[1][0] = 2;
    matrixA[1][1] = 6;
    matrixA[2][0] = 4;
    matrixA[2][1] = 1;
    ASSERT_EQ(3, matrixA.getRows());
    ASSERT_EQ(2, matrixA.getColumns());
    std::cout << matrixA << std::endl;
}

TEST(TestUtils, 1_1_matrix)
{
    Matrix matrixA(1, 1);
    ASSERT_EQ(1, matrixA.getRows());
    ASSERT_EQ(1, matrixA.getColumns());
    matrixA[0][0] = 4;
    ASSERT_EQ(4, matrixA[0][0]);
}

TEST(TestUtils, 1_5_matrix)
{
    Matrix matrixA(1, 5);
    ASSERT_EQ(1, matrixA.getRows());
    ASSERT_EQ(5, matrixA.getColumns());
    matrixA[0][0] = 1;
    matrixA[0][1] = 2;
    matrixA[0][2] = 3;
    matrixA[0][3] = 4;
    matrixA[0][4] = 5;
    ASSERT_EQ(1, matrixA[0][0]);
    ASSERT_EQ(2, matrixA[0][1]);
    ASSERT_EQ(3, matrixA[0][2]);
    ASSERT_EQ(4, matrixA[0][3]);
    ASSERT_EQ(5, matrixA[0][4]);
}

TEST(TestUtils, 5_1_matrix)
{
    Matrix matrixA(5, 1);
    ASSERT_EQ(5, matrixA.getRows());
    ASSERT_EQ(1, matrixA.getColumns());
    matrixA[0][0] = 1;
    matrixA[1][0] = 2;
    matrixA[2][0] = 3;
    matrixA[3][0] = 4;
    matrixA[4][0] = 5;
    ASSERT_EQ(1, matrixA[0][0]);
    ASSERT_EQ(2, matrixA[1][0]);
    ASSERT_EQ(3, matrixA[2][0]);
    ASSERT_EQ(4, matrixA[3][0]);
    ASSERT_EQ(5, matrixA[4][0]);
}

TEST(TestUtils, check_sum)
{
    Matrix matrixA(3, 2);
    Matrix matrixB(3, 2);
    Matrix matrixCheck(3, 2);

    
    matrixA[0][0] = 5;
    matrixA[0][1] = 3;
    matrixA[1][0] = 2;
    matrixA[1][1] = 6;
    matrixA[2][0] = 4;
    matrixA[2][1] = 1;

    std::cout << matrixA << std::endl;
    
    matrixB[0][0] = 4;
    matrixB[0][1] = 5;
    matrixB[1][0] = 2;
    matrixB[1][1] = 2;
    matrixB[2][0] = 4;
    matrixB[2][1] = 7;

    Matrix sumMatrix = matrixA + matrixB;

  
    matrixCheck[0][0] = 9;
    matrixCheck[0][1] = 8;
    matrixCheck[1][0] = 4;
    matrixCheck[1][1] = 8;
    matrixCheck[2][0] = 8;
    matrixCheck[2][1] = 8;

    bool equal = (sumMatrix == matrixCheck);
    ASSERT_EQ(equal, 1);
}

TEST(TestUtils, check_sum_diff)
{
    Matrix matrixA(3, 2);
    Matrix matrixB(3, 1);
    Matrix matrixCheck(3, 2);

    
    matrixA[0][0] = 5;
    matrixA[0][1] = 3;
    matrixA[1][0] = 2;
    matrixA[1][1] = 6;
    matrixA[2][0] = 4;
    matrixA[2][1] = 1;


    
    matrixA[0][0] = 4;
    matrixA[0][1] = 5;

  
    EXPECT_THROW({
        try
        {
            Matrix sumMatrix = matrixA + matrixB;
        }
        catch( const std::out_of_range& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Sizes are different!", e.what() );
            throw;
        }
    }, std::out_of_range );
    
}

TEST(TestUtils, check_out)
{
    Matrix matrixA(1, 1);
    EXPECT_THROW({
        try
        {
            matrixA[1][0] = 5;
        }
        catch( const std::out_of_range& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Sizes are different!", e.what() );
            throw;
        }
    }, std::out_of_range );
    
}

TEST(TestUtils, out_test )
{
    std::ostringstream out;
    Matrix matrixA(3, 2);
    std::cout << matrixA <<std::endl;
    
    matrixA[0][0] = 5;
    matrixA[0][1] = 3;
    matrixA[1][0] = 2;
    matrixA[1][1] = 6;
    matrixA[2][0] = 4;
    matrixA[2][1] = 1;
    std::cout << matrixA <<std::endl;
    out << matrixA;
    
    EXPECT_EQ( "5\t3\n2\t6\n4\t1\n", out.str() );
}

TEST(TestUtils, check_out1)
{
    Matrix matrixA(1, 1);
    EXPECT_THROW({
        try
        {
            matrixA[0][1] = 5;
        }
        catch( const std::out_of_range& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Sizes are different!", e.what() );
            throw;
        }
    }, std::out_of_range );
    
}

TEST(TestUtils, check_mult)
{
    Matrix matrixA(2, 2);
    
    matrixA[0][0] = 1;
    matrixA[0][1] = 1;
    matrixA[1][0] = 1;
    matrixA[1][1] = 1;
    std::cout << "before mult" << std::endl;
    std::cout << matrixA << std::endl;
    matrixA *= 5;
    std::cout << "after mult" << std::endl;
    std::cout << matrixA << std::endl;
    Matrix matrixCheck(2, 2);

    matrixCheck[0][0] = 5;
    matrixCheck[0][1] = 5;
    matrixCheck[1][0] = 5;
    matrixCheck[1][1] = 5;
    std::cout << "to check" << std::endl;
    std::cout << matrixCheck << std::endl;
    bool equal = (matrixA == matrixCheck);
    ASSERT_EQ(equal, 1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
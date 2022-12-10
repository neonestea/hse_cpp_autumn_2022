#include <gtest/gtest.h>
#include <iostream>
#include "bigint.cpp"
#include <string>


class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestUtils, check_equal)
{
    BigInt bigint("1234567891234567891234");
    BigInt bigint1("1234567891234567891234");
    BigInt bigint2("-1234567891234567891234");
    bool eq1 = (bigint == bigint1);
    bool eq2 = (bigint == bigint2);
    ASSERT_EQ(eq1, 1);
    ASSERT_EQ(eq2, 0);
}

TEST(TestUtils, check_bigger)
{
    BigInt bigint("1234567891234567891234");
    BigInt bigint1("1234567891234567891234");
    BigInt bigint2("-1234567891234567891234");
    bool bigger1 = (bigint > bigint1);
    bool bigger3 = (bigint > bigint2);
    ASSERT_EQ(bigger1, 0);
    ASSERT_EQ(bigger3, 1);
}

TEST(TestUtils, check_smaller)
{
    BigInt bigint("1234567891234567891234");
    BigInt bigint1("1234567891234567891234");
    BigInt bigint2("-1234567891234567891234");
    bool smaller1 = (bigint < bigint1);
    bool smaller3 = (bigint < bigint2);
    ASSERT_EQ(smaller1, 0);
    ASSERT_EQ(smaller3, 0);
}

TEST(TestUtils, check_int_sum)
{
    
    BigInt sum44("1234567891");
    BigInt res9 = sum44 + 12345;
    std::string str21 = res9.to_string();
    std::cout << str21 << std::endl;
    bool eq = (str21 == "01234580236");
    ASSERT_EQ(eq, 1);
}

TEST(TestUtils, check_bigint_sum)
{
    
    BigInt sum45("1234567891");
    BigInt sum2("12345");
    BigInt res8 = sum45 + sum2;
    std::string str23 = res8.to_string();
    bool eq = (str23 == "01234580236");
    ASSERT_EQ(eq, 1);
    
}

TEST(TestUtils, check_bigint_diff)
{
    BigInt sum11("1234567891");
    BigInt sum2("12345");
    BigInt res3 = sum11 - sum2;
    std::string str = res3.to_string();
    ASSERT_EQ(str, "1234555546");
}

TEST(TestUtils, check_int_diff)
{
    
    BigInt sum11("1234567891");
    BigInt res3 = sum11 - 12345;
    std::string str = res3.to_string();
    ASSERT_EQ(str, "1234555546");
}

TEST(TestUtils, check_bigint_mult)
{
    BigInt mul66("12");
    BigInt mul12("2");
    BigInt res6 = mul66 * mul12;
    std::cout << "Mult res:" << std::endl;
    std::cout << res6 << std::endl;
    std::cout << res6.to_string() << std::endl;
    ASSERT_EQ(res6.to_string(), "24");
}

TEST(TestUtils, check_int_mult)
{
    BigInt mul222("12");
    BigInt res6 = mul222 * 2;
    std::cout << "Mult res:" << std::endl;
    std::cout << res6 << std::endl;
    std::cout << res6.to_string() << std::endl;
    ASSERT_EQ(res6.to_string(), "24");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
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
    std::string b1 = "1234567891234567891234";
    std::string b2 = "-1234567891234567891234";
    BigInt bigint(b1);
    BigInt bigint1(b1);
    BigInt bigint2(b2);
    bool eq1 = (bigint == bigint1);
    bool eq2 = (bigint == bigint2);
    ASSERT_TRUE(eq1);
    ASSERT_FALSE(eq2);
}

TEST(TestUtils, check_bigger)
{
    std::string b1 = "1234567891234567891234";
    std::string b2 = "-1234567891234567891234";
    BigInt bigint(b1);
    BigInt bigint1(b1);
    BigInt bigint2(b2);
    bool bigger1 = (bigint > bigint1);
    bool bigger3 = (bigint > bigint2);
    ASSERT_FALSE(bigger1);
    ASSERT_TRUE(bigger3);
}

TEST(TestUtils, check_smaller)
{
    std::string b1 = "1234567891234567891234";
    std::string b2 = "-1234567891234567891234";
    BigInt bigint(b1);
    BigInt bigint1(b1);
    BigInt bigint2(b2);
    bool smaller1 = (bigint < bigint1);
    bool smaller3 = (bigint < bigint2);
    ASSERT_FALSE(smaller1);
    ASSERT_FALSE(smaller3);
}

TEST(TestUtils, check_int_sum)
{
    std::string s1 = "1234567891";
    BigInt sum44(s1);
    BigInt res9 = sum44 + 12345;
    std::string str21 = res9.to_string();
    //std::cout << str21 << std::endl;
    bool eq = (str21 == "01234580236");
    ASSERT_TRUE(eq);
}

TEST(TestUtils, check_bigint_sum)
{
    std::string b1 = "1234567891";
    std::string b2 = "12345";
    BigInt sum45(b1);
    BigInt sum2(b2);
    BigInt res8 = sum45 + sum2;
    std::string str23 = res8.to_string();
    bool eq = (str23 == "01234580236");
    ASSERT_TRUE(eq);
    
}

TEST(TestUtils, check_bigint_diff)
{
    std::string b1 = "1234567891";
    std::string b2 = "12345";
    BigInt sum11(b1);
    BigInt sum2(b2);
    BigInt res3 = sum11 - sum2;
    std::string str = res3.to_string();
    ASSERT_EQ(str, "1234555546");
}

TEST(TestUtils, check_int_diff)
{
    std::string b1 = "1234567891";
    BigInt sum11(b1);
    BigInt res3 = sum11 - 12345;
    std::string str = res3.to_string();
    ASSERT_EQ(str, "1234555546");
}

TEST(TestUtils, check_bigint_mult)
{
    std::string m1 = "12";
    std::string m2 = "2";
    BigInt mul66(m1);
    BigInt mul12(m2);
    BigInt res6 = mul66 * mul12;
    //std::cout << "Mult res:" << std::endl;
    //std::cout << res6 << std::endl;
    //std::cout << res6.to_string() << std::endl;
    ASSERT_EQ(res6.to_string(), "24");
}

TEST(TestUtils, check_int_mult)
{
    std::string m11 = "12";
    BigInt mul222(m11);
    BigInt res6 = mul222 * 2;
    //std::cout << "Mult res:" << std::endl;
    //std::cout << res6 << std::endl;
    //std::cout << res6.to_string() << std::endl;
    ASSERT_EQ(res6.to_string(), "24");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include <iostream>
#include "parser.cpp"


void addCount(int* count=nullptr)
{
    *count = *count + 1;
}

void setExecuted(bool* executed=nullptr)
{
    *executed = true;
}

void checkLongest(std::string* longest=nullptr, std::string line = "")
{
    std::string tmp = *longest;
    if(tmp.length() < line.length())
    {
        *longest = line;
    }
}

class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestUtils, test_set_start)
{
    TokenParser parser;
    parser.SetStartCallback(&addCount);
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slke2\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    ASSERT_EQ(2, parser.getLinesCount());
}

TEST(TestUtils, test_set_end)
{
    TokenParser parser;
    parser.SetEndCallback(&setExecuted);
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slke2\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    ASSERT_EQ(1, parser.getEndExecuted());
}

TEST(TestUtils, test_set_digit)
{
    TokenParser parser;
    parser.SetDigitTokenCallback(&addCount);
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slke2\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    ASSERT_EQ(3, parser.getNumberOfDigitTokens());
}

TEST(TestUtils, test_set_string)
{
    TokenParser parser;
    parser.SetStringTokenCallback(&checkLongest);
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slke2\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    ASSERT_EQ("18446744073709551616", parser.getLongestLine());

}

TEST(TestUtils, do_not_set)
{
    TokenParser parser;
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slke2\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }

    ASSERT_EQ(0, parser.getEndExecuted());

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
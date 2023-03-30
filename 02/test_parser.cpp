#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <cstdint>
#include "parser.cpp"

std::vector<std::string> string_tokens;  //for string tokens
std::vector<uint64_t> digit_tokens;

void addDigit(uint64_t val)
{
    digit_tokens.push_back(val);
}

void addCount(int* count=nullptr)
{
    *count = *count + 1;
}

void setExecuted(bool* executed=nullptr)
{
    *executed = true;
}

void addString(std::string line)
{
    string_tokens.push_back(line);
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
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slk2e\nadlfk\tdfaadsfads";
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
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slk2e\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    ASSERT_EQ(1, parser.getEndExecuted());
}

TEST(TestUtils, test_set_digit)
{
    std::cout << std::numeric_limits<uint64_t>::max() << std::endl; //MAX UINT64 is 18446744073709551615
    //so 18446744073709551615 and 18446744073709551614 are still digits
    TokenParser parser;
    parser.SetDigitTokenCallback(&addDigit);
    parser.SetStringTokenCallback(nullptr);
    std::string my_line = "Hello wor3ld 1 18446744073709551615 18446744073709551616 18446744073709551614 23423 slke2\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;
    std::vector<std::string> digits;

    digits.push_back("1");
    digits.push_back("18446744073709551615");
    digits.push_back("18446744073709551614");
    digits.push_back("23423");
    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    //std::vector<uint64_t> digits_from_parser = parser.getDigitTokens();
    int size = static_cast<int>(digits.size());
    ASSERT_EQ(digits.size(), digit_tokens.size());
    for (auto  i = 0; i < size; i++)
    {
        ASSERT_EQ(digits[i], std::to_string(digit_tokens[i]));
    }
    
}

TEST(TestUtils, test_set_string)
{
    
    TokenParser parser;
    parser.SetDigitTokenCallback(nullptr);
    parser.SetStringTokenCallback(&addString);
    std::string my_line = "Hello r 18446744073709551615 42str 18446744073709551616 18446744073709551614 23423 slk2e\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;
    std::vector<std::string> strings;
    strings.push_back("Hello");
    strings.push_back("r");
    strings.push_back("42str");
    strings.push_back("18446744073709551616");
    strings.push_back("slk2e");
    strings.push_back("adlfk");
    strings.push_back("dfaadsfads");
    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    //std::vector<std::string> strings_from_parser = parser.getStringTokens();
    int size = static_cast<int>(strings.size());
    
    ASSERT_EQ(strings.size(), string_tokens.size());
    for (auto  i = 0; i < size; i++)
    {
        ASSERT_EQ(strings[i], string_tokens[i]);
    }

}

TEST(TestUtils, test_set_one_digit)
{
    string_tokens.clear();
    digit_tokens.clear();
    std::cout << std::numeric_limits<uint64_t>::max() << std::endl; //MAX UINT64 is 18446744073709551615
    //so 18446744073709551615 and 18446744073709551614 are still digits
    TokenParser parser;
    parser.SetDigitTokenCallback(&addDigit);
    parser.SetStringTokenCallback(nullptr);
    std::string my_line = "1";
    std::istringstream iss(my_line);
    std::string line;
    std::vector<std::string> digits;

    digits.push_back("1");
    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    //std::vector<uint64_t> digits_from_parser = parser.getDigitTokens();
    int size = static_cast<int>(digits.size());
    ASSERT_EQ(digits.size(), digit_tokens.size());
    for (auto  i = 0; i < size; i++)
    {
        ASSERT_EQ(digits[i], std::to_string(digit_tokens[i]));
    }
    
}

TEST(TestUtils, test_set_one_string)
{
    string_tokens.clear();
    digit_tokens.clear();
    TokenParser parser;
    parser.SetDigitTokenCallback(nullptr);
    parser.SetStringTokenCallback(&addString);
    std::string my_line = "r";
    std::istringstream iss(my_line);
    std::string line;
    std::vector<std::string> strings;
    strings.push_back("r");
    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    //std::vector<std::string> strings_from_parser = parser.getStringTokens();
    int size = static_cast<int>(strings.size());
    
    ASSERT_EQ(strings.size(), string_tokens.size());
    for (auto  i = 0; i < size; i++)
    {
        ASSERT_EQ(strings[i], string_tokens[i]);
    }

}

TEST(TestUtils, do_not_set)
{
    
    TokenParser parser;
    parser.SetDigitTokenCallback(nullptr);
    parser.SetStringTokenCallback(nullptr);
    parser.SetEndCallback(nullptr);
    parser.SetStartCallback(nullptr);
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slke2\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }

    ASSERT_EQ(0, parser.getEndExecuted());

}

TEST(TestUtils, set_null)
{
    TokenParser parser;
    parser.SetDigitTokenCallback(nullptr);
    parser.SetStringTokenCallback(nullptr);
    parser.SetEndCallback(nullptr);
    parser.SetStartCallback(nullptr);
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    string_tokens.clear();
    digit_tokens.clear();
    //std::vector<std::string> strings_from_parser = parser.getStringTokens();
    int sizeStrings = static_cast<int>(string_tokens.size());
    ASSERT_EQ(0, sizeStrings);

    //std::vector<uint64_t> digits_from_parser = parser.getDigitTokens();
    int sizeDigits = static_cast<int>(digit_tokens.size());
    ASSERT_EQ(0, sizeDigits);
    ASSERT_EQ(0, parser.getEndExecuted());
    ASSERT_EQ(0, parser.getLinesCount());

}

TEST(TestUtils, empty_str)
{
    TokenParser parser;
    parser.SetDigitTokenCallback(nullptr);
    parser.SetStringTokenCallback(nullptr);
    parser.SetEndCallback(nullptr);
    parser.SetStartCallback(nullptr);
    std::string my_line = "";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    string_tokens.clear();
    digit_tokens.clear();
    //std::vector<std::string> strings_from_parser = parser.getStringTokens();
    int sizeStrings = static_cast<int>(string_tokens.size());
    ASSERT_EQ(0, sizeStrings);

    //std::vector<uint64_t> digits_from_parser = parser.getDigitTokens();
    int sizeDigits = static_cast<int>(digit_tokens.size());
    ASSERT_EQ(0, sizeDigits);
    ASSERT_EQ(0, parser.getEndExecuted());
    ASSERT_EQ(0, parser.getLinesCount());

}

TEST(TestUtils, only_spaces)
{
    TokenParser parser;
    parser.SetDigitTokenCallback(nullptr);
    parser.SetStringTokenCallback(nullptr);
    parser.SetEndCallback(nullptr);
    parser.SetStartCallback(nullptr);
    std::string my_line = "          ";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }
    string_tokens.clear();
    digit_tokens.clear();
    //std::vector<std::string> strings_from_parser = parser.getStringTokens();
    int sizeStrings = static_cast<int>(string_tokens.size());
    ASSERT_EQ(0, sizeStrings);

    //std::vector<uint64_t> digits_from_parser = parser.getDigitTokens();
    int sizeDigits = static_cast<int>(digit_tokens.size());
    ASSERT_EQ(0, sizeDigits);
    ASSERT_EQ(0, parser.getEndExecuted());
    ASSERT_EQ(0, parser.getLinesCount());

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include <iostream>
#include "formatter.cpp"
#include <string>



class TestFoo : public ::testing::Test
{
    protected: 
        void SetUp() {}
        void TearDown() {}
};

TEST(TestUtils, check_correct) //Правильный случай
{
    std::stringstream stream;
    std::string line = "Hello, {0}. What a beautiful {1}! It is {2} that everything is {2}";
    Formatter formatter(stream, line);

    formatter(3, "day", true);
    std::string res = formatter.getString();
    std::string correct = "Hello, 3. What a beautiful day! It is true that everything is true";
    ASSERT_EQ(correct, res);
}

TEST(TestUtils, check_incorrect_brackets)  //Скобки либо не совпадают, либо в неправильном порядке, либо одна скобка 
{
    std::stringstream stream;
    std::string line = "Hello, {0}. What a bea{utiful {1}! It is {2} that everything is {2}";
    Formatter formatter(stream, line);
    EXPECT_THROW({
        try
        {
            formatter(3, "day", true);
            std::string res = formatter.getString();
        }
        catch( const BracketsMismatchException& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Mismatch of {}", e.what() );
            throw;
        }
    }, BracketsMismatchException );

    
    EXPECT_THROW({
        try
        {
            formatter(3, "day", true);
            std::string res = formatter.getString();
        }
        catch( const BracketsMismatchException& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Mismatch of {}", e.what() );
            throw;
        }
    }, BracketsMismatchException );
    
}

TEST(TestUtils, check_empty_brackets)  //Скобки есть, но внутри них ничего нет
{
   
    std::stringstream stream;
    std::string line = "Hello, {0}. What a bea{}utiful {1}! It is {2} that everything is {2}";
    Formatter formatter(stream, line);
    EXPECT_THROW({
        try
        {
            formatter(3, "day", true);
            std::string res = formatter.getString();
        }
        catch( const EmptyParamException& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Empty param number", e.what() );
            throw;
        }
    }, EmptyParamException );
    
}

TEST(TestUtils, check_not_a_number) //Скобки есть, но внутри не число
{
   
    std::stringstream stream;
    std::string line = "Hello, {0}. What a bea{d}utiful {1}! It is {2} that everything is {2}";
    Formatter formatter(stream, line);
    EXPECT_THROW({
        try
        {
            formatter(3, "day", true);
            std::string res = formatter.getString();
        }
        catch( const NotANumberException& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Not a number", e.what() );
            throw;
        }
    }, NotANumberException );
    
}

TEST(TestUtils, check_incorrect_number_of_parameters)
{
   std::stringstream stream;
    std::string line = "Hello, {0}. What a beautiful {1}! It is {2} that everything is {3}"; //параметров в строке больше, чем мы предоставили
    Formatter formatter(stream, line);
    EXPECT_THROW({
        try
        {
            formatter(3, "day", true);
            std::string res = formatter.getString();
        }
        catch( const IncorrectParamsNumberException& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Incorrect Number of Params", e.what() );
            throw;
        }
    }, IncorrectParamsNumberException );

    std::stringstream stream1;
    std::string line1 = "Hello, {1}. What a beautiful {2}! It is {3} that everything is {3}"; //параметры не с 0
    Formatter formatter1(stream1, line1);
    EXPECT_THROW({
        try
        {
            formatter1(3, "day", true);
            std::string res = formatter1.getString();
        }
        catch( const IncorrectParamsNumberException& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Number of params is incorrect!", e.what() );
            throw;
        }
    }, IncorrectParamsNumberException );

}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
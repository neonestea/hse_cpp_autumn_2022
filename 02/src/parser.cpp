#include <iostream>
#include <sstream>
#include <ctype.h>


class TokenParser

{

public:

    //TokenParser() = default;

    //using FuncPtr = void(*)();
    using FuncBoolPtr = void(*)(bool*);
    using FuncIntPtr = void(*)(int*);
    using FuncStringStringPtr = void(*)(std::string*, std::string);


    FuncIntPtr startCallbackPtr = nullptr;
    FuncBoolPtr endCallbackPtr = nullptr;
    FuncStringStringPtr stringTokenCallbackPtr = nullptr;
    FuncIntPtr digitTokenCallbackPtr = nullptr;

    bool end_executed = false;  //for end
    std::string longest_line = "";  //for string tokens
    int number_of_digit_tokens = 0;  //for digit tokens
    int lines_count = 0; //for start

    bool getEndExecuted() {
        return end_executed;
    }

    std::string getLongestLine() {
        return longest_line;
    }

    int getNumberOfDigitTokens() {
        return number_of_digit_tokens;
    }

    int getLinesCount() {
        return lines_count;
    }

    // Устанавливаем callback-функцию перед стартом парсинга.

    void SetStartCallback(const FuncIntPtr& funcPtr)
    {
        startCallbackPtr = funcPtr;
        std::cout << "Set start " << std::endl;
    }



    // Устанавливаем callback-функцию после окончания парсинга.

    void SetEndCallback(const FuncBoolPtr& funcPtr)
    {
        endCallbackPtr = funcPtr;
    }



    // Устанавливаем callback-функцию для обработки чисел.

    void SetDigitTokenCallback(const FuncIntPtr& funcPtr)
    {
        digitTokenCallbackPtr = funcPtr;
    }


    // Устанавливаем callback-функцию для обработки строк.

    void SetStringTokenCallback(const FuncStringStringPtr& funcPtr)
    {
        stringTokenCallbackPtr = funcPtr;
    }
    

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), 
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }

    void Parse(const std::string &str) 
    {   
        if (startCallbackPtr != nullptr) {
            startCallbackPtr(&lines_count);
        }
        const std::string MAX_UINT64 = "18446744073709551615";
        std::string string_to_parse = str;

        // Replace \t by spaces
        size_t pos = string_to_parse.find("\t");
        while( pos != std::string::npos)
        {
            string_to_parse.replace(pos, 1, " ");
            pos = string_to_parse.find("\t", pos + 1);
        }
        std::string next = "";

        int num_of_symbols = string_to_parse.length();
        for(std::string::iterator it = string_to_parse.begin(); it != string_to_parse.end(); ++it) {
            //if next symbol is a separator or this is the last symbol we check token
            if (num_of_symbols == 1 || *it == ' ')
            {
                std::cout << "Our token is:  " << next << std::endl;
                if (is_number(next) == 1) 
                {
                    //check if matches UINT64
                    if (next.length() > MAX_UINT64.length() || (next.length() == MAX_UINT64.length() && next > MAX_UINT64))
                    {
                        if (stringTokenCallbackPtr != nullptr) {
                            stringTokenCallbackPtr(&longest_line, next);
                        }
                        std::cout << "String token" << std::endl;
                    }
                    else
                    {

                        if (digitTokenCallbackPtr != nullptr) {
                            std::cout << "Digit token" << std::endl;
                            digitTokenCallbackPtr(&number_of_digit_tokens);
                        }
                        
                    }
                }
                else 
                {
                    if (stringTokenCallbackPtr != nullptr) {
                        stringTokenCallbackPtr(&longest_line, next);
                    }
                    std::cout << "String token" << std::endl;
                }
                next = "";
                
            }

            //else we add symbol to tocken
            else
            {
                next += *it;
            }
            num_of_symbols--;
            if (num_of_symbols == 0) 
            {
                std::cout << "This is the end" << std::endl;
                if (endCallbackPtr != nullptr) {
                    endCallbackPtr(&end_executed);
                }
            }
        }
        


    }

};
/*void addCount(int* count=nullptr)
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


int main()

{
    TokenParser parser;
    parser.SetStartCallback(&addCount);
    parser.SetEndCallback(&setExecuted);
    parser.SetDigitTokenCallback(&addCount);
     parser.SetStringTokenCallback(&checkLongest);
    std::string my_line = "Hello wor3ld 18446744073709551615 18446744073709551616 18446744073709551614 23423 slke2\nadlfk\tdfaadsfads";
    std::istringstream iss(my_line);
    std::string line;

    while (std::getline(iss, line)) {
        parser.Parse(line);
    }

    std::cout << "Lines count: " << parser.getLinesCount() << std::endl;
    std::cout << "End executed: " << parser.getEndExecuted() << std::endl;
    std::cout << "Number of digit tokens: " << parser.getNumberOfDigitTokens() << std::endl;
    std::cout << "Longest line: " << parser.getLongestLine() << std::endl;

    return 0;
}*/
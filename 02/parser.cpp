#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <ctype.h>
class TokenParser

{

public:

    //TokenParser() = default;

    //using FuncPtr = void(*)();
    using FuncBoolPtr = void(*)(bool*);
    using FuncInt64Ptr = void(*)(uint64_t);
    using FuncIntPtr = void(*)(int*);
    using FuncStringStringPtr = void(*)(std::string);


    FuncIntPtr startCallbackPtr = nullptr;
    FuncBoolPtr endCallbackPtr = nullptr;
    FuncStringStringPtr stringTokenCallbackPtr = nullptr;
    FuncInt64Ptr digitTokenCallbackPtr = nullptr;

    bool end_executed = false;  //for end
    
    int lines_count = 0; //for start

    bool getEndExecuted() {
        return end_executed;
    }

    int getLinesCount()
    {
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

    void SetDigitTokenCallback(const FuncInt64Ptr& funcPtr)
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
        std::string string_to_parse = str;
        const std::string MAX_UINT64 = "18446744073709551615";
        std::cout << "Our string is:  " << string_to_parse << std::endl;
        // Replace \t by spaces
        size_t pos = string_to_parse.find("\t");
        size_t posn = string_to_parse.find("\n");
        while( pos != std::string::npos)
        {
            string_to_parse.replace(pos, 1, " ");
            pos = string_to_parse.find("\t", pos + 1);
        }
        while( posn != std::string::npos)
        {
            string_to_parse.replace(posn, 1, " ");
            posn = string_to_parse.find("\n", posn + 1);
        }
        std::string next = "";
        std::cout << "Our string is:  " << string_to_parse << std::endl;
        int num_of_symbols = string_to_parse.length();
        for(std::string::iterator it = string_to_parse.begin(); it != string_to_parse.end(); ++it) {
            //if next symbol is a separator or this is the last symbol we check token
            //std::cout << "Our letter is:  " << *it << std::endl;
            //std::cout << "num_of_symbols is:  " << num_of_symbols << std::endl;
            if (num_of_symbols == 1 || *it == ' ')
            {
                if (num_of_symbols == 1 )
                {
                    next += *it;
                }
                std::cout << "Our token is:  " << next << std::endl;
                if (is_number(next) == 1) 
                {
                    //check if matches UINT64
                    if (next.length() > MAX_UINT64.length() || (next.length() == MAX_UINT64.length() && next > MAX_UINT64))
                    {
                        if (stringTokenCallbackPtr != nullptr) {
                            //std::string token_str = 
                            stringTokenCallbackPtr(next);
                            //vec.push_back(token_str);
                        }
                        std::cout << "String token" << std::endl;
                    }
                    else
                    {

                        if (digitTokenCallbackPtr != nullptr) {
                            std::cout << "Digit token" << std::endl;
                            uint64_t value;
                            std::istringstream iss(next);
                            iss >> value;
                            //uint64_t digit_str = 
                            digitTokenCallbackPtr(value);
                           //digit_tokens.push_back(digit_str);
                        }
                        
                    }
                }
                else 
                {
                    if (stringTokenCallbackPtr != nullptr) {
                        //std::string token_str = 
                        stringTokenCallbackPtr(next);
                        //string_tokens.push_back(token_str);
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

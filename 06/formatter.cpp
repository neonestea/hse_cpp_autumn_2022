#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <set>
#include <algorithm>
#include "exception.hpp"

class Formatter
{
    static constexpr char Separator = ' ';
public:
    explicit Formatter(std::stringstream& out, std::string& s)
        : out_(out), line_(s)
    {}

    template <class T, class... ArgsT>
    void operator()(T&& val, ArgsT&&... args)
    {
        count++;
        out_ << std::boolalpha;
        out_ << Separator;
        out_ << val;
        
        //std::string value = std::to_string(val);
        //params_.push_back(value);
        (*this)(std::forward<ArgsT>(args)...);
    }

    template <class T>
    void operator()(T&& val)
    {
        count++;
        //std::cout << "Processing " << val << std::endl;
        //std::cout << typeid(val).name() << std::endl;

        out_ << std::boolalpha;
        out_ << Separator;
        out_ << val;
    }


    void getParams() {
        //const std::string& str = out_.str();
        //params_.assign( str.begin(), str.end() );
        std::string text;
        for(int i = 0; i < count; i++)
         {
            out_ >> text;
            //std::cout << text << std::endl;
            params_.push_back(text);
            
        }
        
    }

    //Регулярки нельзя
    /*void checkString()
    {

        std::regex rex{ "\\{(\\d+)\\}" };
        std::sregex_iterator beg{ line_.cbegin(), line_.cend(), rex };
        std::sregex_iterator end{}; 
        int paramsCounter = 0;

        for (auto i = beg; i != end; ++i)
        { 
            paramsCounter++;
            std::cout << i->str() << std::endl;
        }
        if (paramsCounter != count)
        {
            std::cout << "Params mismatch! Exception here!" << std::endl;
        }
    }*/

    std::string getString()
    {
        try{
        getParams();
        std::set<int> paramsToChange = checkString();
        int i = 0;
        for(auto it = paramsToChange.begin(); it != paramsToChange.end(); it++,i++ )
        {
            std::cout << "It: " << *it << " patams_.size is " << params_.size() << std::endl;
            if ((unsigned)*it > params_.size() - 1)
            {
                std::cout << "ERROR. Number of params is incorrect!" << std::endl;
                throw IncorrectParamsNumberException("Number of params is incorrect!");
            }
            std::cout << "{" << *it << "}" << std::endl;
            std::cout << "To replace with " << params_[*it] << std::endl;
            std::string to = params_[*it];
            std::string substr = "{" + std::to_string(*it) + "}";
            std::cout << "Replacing all " << substr << " to " << to << std::endl;
            replaceAll(line_, substr, to);
        }
        std::stringstream().swap(out_);
        out_ << line_;
        } catch( const IncorrectParamsNumberException& e )
        {
            
            throw;
        }
        return line_;
    }

    void replaceAll(std::string& str, const std::string& from, const std::string& to) {
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }

    std::set<int> checkString()
    {
        std::set<int> params;
        try {
            int counter = 0;
            std::vector<int> openPositions;
            std::vector<int> closePositions;
            for(std::string::iterator it = line_.begin(); it != line_.end(); ++it)
            {
                
                if(*it == '{')
                {
                    openPositions.push_back(counter);
                }
                if(*it == '}')
                {
                    closePositions.push_back(counter);
                }
                counter++;
            }
            if (openPositions.size() != closePositions.size())
            {
                std::cout << "ERROR. Mismatch of {}!" << std::endl;
                throw BracketsMismatchException("Mismatch of {}");
                
            }

            int i = 0;
            //int paramsCounter = 0;
            
            for(auto it = openPositions.begin(); it != openPositions.end(); it++,i++ )
            {
                std::cout << "Open pos = " << *it << std::endl;
                std::cout << "Close pos = " << closePositions[i] << std::endl;

                int closePos = closePositions[i];
                if (closePos < *it || closePos == *it + 1)
                {
                    std::cout << "ERROR. Empty param number!" << std::endl;
                    throw EmptyParamException("Empty param number");
                }
                int length = closePos - *it + 1;
                std::string param = line_.substr(*it, length);
                std::cout << "found " << param << std::endl;
                std::cout << "length " << param.length() << std::endl;
                std::string between =  param.substr(1, param.length() - 2);
                if (is_number(between))
                {
                    std::cout << "Number " << between << std::endl;
                    params.insert(atoi( between.c_str() ));
                }
                else
                {
                    std::cout << "ERROR. Not a number!" << std::endl;
                    throw NotANumberException("Not a number");
                }
            }
            std::cout << "Input params size = " << params_.size() << std::endl;
            std::cout << "In string params size = " << params.size() << std::endl;
            if (params_.size() !=  params.size())
            {
                std::cout << "ERROR. Number of params is incorrect!" << std::endl;
                throw IncorrectParamsNumberException("Incorrect Number of Params");
            }
        } catch( const IncorrectParamsNumberException& e)
        {
            throw;
        } catch (const BracketsMismatchException& e)
        {
            throw;
        } catch (const EmptyParamException& e)
        {
            throw;
        } catch (const NotANumberException& e)
        {
            throw;
        }
        return params;

    }

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), 
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }

    void printCount()
    {
        std::cout << "Counter = " << count << std::endl;
    }

    void printVector()
    {
        int i = 0;
        for(auto it = params_.begin(); it != params_.end(); it++,i++ )
         {
            std::cout << *it << std::endl;  
            
        }
    }

    
    
private:
    std::stringstream& out_;
    std::string& line_;
    int count = 0;
    std::vector<std::string> params_;
};

/*int main()
{
    std::stringstream stream;
    std::string line = "Hello, {0}. What a beautiful {1}!";
    Formatter formatter(stream, line);

    formatter(3, "day");
    //std::cout << stream std::endl;
    //formatter.getParams();
    //formatter.printVector();
    //formatter.printCount();
    //formatter.checkString();
    std::string res = formatter.getString();
    std::cout << res << std::endl;
    return 0;
}*/
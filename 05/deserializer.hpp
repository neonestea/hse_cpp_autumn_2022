#pragma once
#include <iostream>
#include <sstream>
#include <cstdint>

class Deserializer
{
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {}


    template <class T>
    Error load(T& object)
    {
        //std::cout << "Deserialize" << std::endl;
        return object.deserialize(*this);
    }

    template <class T, class... ArgsT>
    Error operator()(T&& val, ArgsT&&... args)
    {
        Error err = load(val);
        if (err == Error::NoError)
        {
            //std::cout << "NoError!" << std::endl;
        }
        else
        {
            //std::cout << "CorruptedArchive!" << std::endl;
            return Error::CorruptedArchive;
        }
        return (*this)(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error operator()(T&& val)
    {
        return load(val);
    }

    Error load(bool& value)
    {
        std::string text;
        in_ >> text;
        //std::cout << "try to deserialize bool: " << text << std::endl;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
        {
            //std::cout << "CorruptedArchive: " << text << std::endl;
            return Error::CorruptedArchive;
        }
        //std::cout << "NoError: " << text << std::endl;
            
        return Error::NoError;
    }

    Error load(uint64_t& value)
    {
        std::string text;
        in_ >> text;
        //std::cout << "try to deserialize int: " << text << std::endl;

        if (isNumeric(text))
        {
            std::istringstream iss(text);
            iss >> value;
        }
        else
        {
            //std::cout << "CorruptedArchive: " << text << std::endl;
            return Error::CorruptedArchive;
        }
            
        //std::cout << "NoError: " << text << std::endl;
        return Error::NoError;
    }

    bool isNumeric(std::string const &str)
    {
        auto it = str.begin();
        while (it != str.end() && std::isdigit(*it)) {
            it++;
        }
        return !str.empty() && it == str.end();
    }
    
private:
    std::istream& in_;
};
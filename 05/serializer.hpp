#pragma once
#include <iostream>
#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive
};



class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {}


    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

//variadic templates
    template <class T, class... ArgsT>
    Error operator()(T&& val, ArgsT&&... args)
    {
        process(val);
        return (*this)(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error operator()(T&& val)
    {
        return process(val);
    }

    Error process(bool &arg)
    {
        std::cout << "try to serialize bool: " << arg << std::endl;
        std::string val;
        if (arg)
        {
            val = "true";
        }
        else
        {
            val = "false";
        }
        std::cout << "result bool: " << val << std::endl;
        if (out_.tellp() == std::streampos(0))
        {
            out_ << val;
        }
        else 
        {
            out_ << Separator;
            out_ << val;
        }
        return Error::NoError;
    }

    Error process(uint64_t &arg)
    {
        std::cout << "try to serialize int: " << arg << std::endl;
        if (out_.tellp() == std::streampos(0))
        {
            out_ << arg;
        }
        else 
        {
            out_ << Separator;
            out_ << arg;
        }
        return Error::NoError;
    }

    
private:
    std::ostream& out_;
};
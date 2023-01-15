#include <exception>
#include <iostream>
#include <string>
#pragma once

class IncorrectParamsNumberException : public std::exception
{
    std::string _msg;
public:
    IncorrectParamsNumberException(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};

class BracketsMismatchException : public std::exception
{
    std::string _msg;
public:
    BracketsMismatchException(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};

class EmptyParamException : public std::exception
{
    std::string _msg;
public:
    EmptyParamException(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};

class NotANumberException : public std::exception
{
    std::string _msg;
public:
    NotANumberException(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};
#include <exception>
#include <iostream>
#include <string>
#pragma once

class ElementNotExistst : public std::exception
{
    std::string _msg;
public:
    ElementNotExistst(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};


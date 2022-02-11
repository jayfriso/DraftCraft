#pragma once

#include <stdexcept>
#include <string>

class ModelLogicError : public std::logic_error 
{
public:
    explicit ModelLogicError(const std::string& _Message) : std::logic_error(_Message) {}
};
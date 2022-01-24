#pragma once

#include <stdexcept>

class ModelLogicError : public std::logic_error 
{
public:
    explicit ModelLogicError(const string& _Message) : std::logic_error(_Message) {}
};
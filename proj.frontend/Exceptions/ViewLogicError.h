#pragma once

#include <stdexcept>
#include <string>

class ViewLogicError : public std::logic_error
{
public:
    explicit ViewLogicError(const std::string& _Message) : std::logic_error(_Message) {}
};


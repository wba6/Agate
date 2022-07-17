#pragma once
#include <exception>

class OutOfBonds : public std::exception {

public:
    char const *what() const override
    {
        return "Out of bonds exception";
    }
};

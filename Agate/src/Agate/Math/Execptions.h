#pragma once
#include <exception>

class OutOfBonds : public std::exception {

public:
    virtual const char *what() const noexcept  override
    {
        return "Out of bonds exception";
    }
     ~OutOfBonds()  noexcept{};
};

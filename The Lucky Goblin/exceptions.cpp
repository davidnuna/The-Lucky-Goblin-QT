#include "exceptions.h"

const char* VALIDATION_ERROR::what() const throw()
{
    return this->ErrorMessage.c_str();
}

const char* REPOSITORY_ERROR::what() const throw()
{
    return this->ErrorMessage.c_str();
}
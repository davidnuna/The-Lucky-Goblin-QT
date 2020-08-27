#pragma once
#include <exception>
#include <string>

using namespace std;


class VALIDATION_ERROR : public exception
{
private:
    string ErrorMessage;
public:
    VALIDATION_ERROR(const string& Message) : ErrorMessage(Message) {}
    virtual const char* what() const throw();
};

class REPOSITORY_ERROR : public exception
{
private:
    string ErrorMessage;
public:
    REPOSITORY_ERROR(const string& Message) : ErrorMessage(Message) {}
    virtual const char* what() const throw();
};
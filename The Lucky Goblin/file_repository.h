#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "exceptions.h"

using namespace std;

template<typename ClassType>
class SERVANT_REPOSITORY
{
protected:
    string FileLocation;
    virtual vector<ClassType> ReadFromFile() = 0;
    virtual void WriteToFile(vector<ClassType> vectorToWrite) = 0;
public:
    virtual ~SERVANT_REPOSITORY() = default;
    void SaveElement(ClassType NewElement);
    void UnsaveElement(ClassType DeletedElement);
    virtual void Display() = 0;
    void SetFileLocation(string FileLocation);
    vector<ClassType> GetVector();
    string GetFileLocation();
};
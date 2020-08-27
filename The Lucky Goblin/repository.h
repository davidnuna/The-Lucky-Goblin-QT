#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "exceptions.h"

using namespace std;

template<typename ClassType>
class BASE_REPOSITORY_CUSTODIAN
{
protected:
    string FileLocation;
    int Index = 0;
    virtual vector<ClassType> ReadVector() = 0;
    virtual void WriteVector(vector<ClassType>vectorToOutput) = 0;
public:
    virtual ~BASE_REPOSITORY_CUSTODIAN() = default;
    virtual void AddElement(ClassType NewElement) = 0;
    virtual void DeleteElement(ClassType ElementToDelete) = 0;
    virtual void UpdateElement(ClassType UpdatedElement) = 0;
    virtual ClassType SearchElement(ClassType ElementToSearchBy) = 0;
    virtual vector<ClassType> GetVector() = 0;
    virtual void SetFileLocation(string FileLocation) = 0;
    virtual int GetIndex() = 0;
    virtual void SetIndex(int NewIndex) = 0;
};

template<typename ClassType>
class FILE_REPOSITORY_CUSTODIAN : public BASE_REPOSITORY_CUSTODIAN<ClassType>
{
private:
    vector<ClassType> ReadVector() override;
    void WriteVector(vector<ClassType>vectorToOutput) override;
public:
    FILE_REPOSITORY_CUSTODIAN() { this->FileLocation = "Tasks.txt"; };
    void AddElement(ClassType NewElement) override;
    void DeleteElement(ClassType ElementToDelete) override;
    void UpdateElement(ClassType UpdatedElement) override;
    ClassType SearchElement(ClassType ElementToSearchBy) override;
    vector<ClassType> GetVector() override;
    void SetFileLocation(string FileLocation) override;
    int GetIndex() override;
    void SetIndex(int NewIndex) override;
};

template<typename ClassType>
class MEMORY_REPOSITORY_CUSTODIAN : public BASE_REPOSITORY_CUSTODIAN<ClassType>
{
private:
    vector<ClassType> TasksVector;
    vector<ClassType> ReadVector() override { return vector<ClassType>(); };
    void WriteVector(vector<ClassType>vectorToOutput) override {};
public:
    void AddElement(ClassType NewElement) override;
    void DeleteElement(ClassType ElementToDelete) override;
    void UpdateElement(ClassType UpdatedElement) override;
    ClassType SearchElement(ClassType ElementToSearchBy) override;
    vector<ClassType> GetVector() override;
    void SetFileLocation(string FileLocation) override {};
    int GetIndex() override;
    void SetIndex(int NewIndex) override;
};

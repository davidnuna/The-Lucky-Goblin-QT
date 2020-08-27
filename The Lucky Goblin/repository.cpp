#include "repository.h"

// IN-MEMORY REPOSITORY

template<typename ClassType>
void MEMORY_REPOSITORY_CUSTODIAN<ClassType>::AddElement(ClassType NewElement)
{
    for (auto& classItem : this->TasksVector)
        if (classItem == NewElement)
            throw REPOSITORY_ERROR("Element already present in the list!\n\n");
    this->TasksVector.push_back(NewElement);
}

template<typename ClassType>
void MEMORY_REPOSITORY_CUSTODIAN<ClassType>::DeleteElement(ClassType ElementToDelete)
{
    int currentIndex = 0;
    for (auto& classItem : this->TasksVector)
    {
        if (classItem == ElementToDelete)
        {
            this->TasksVector.erase(this->TasksVector.begin() + currentIndex);
            return;
        }
        currentIndex++;
    }
    throw REPOSITORY_ERROR("Element not found in the list!\n\n");
}

template<typename ClassType>
void MEMORY_REPOSITORY_CUSTODIAN<ClassType>::UpdateElement(ClassType UpdatedElement)
{
    for (auto& classItem : this->TasksVector)
        if (classItem == UpdatedElement)
        {
            classItem = UpdatedElement;
            return;
        }
    throw REPOSITORY_ERROR("Element not found in the list!\n\n");
}


template<typename ClassType>
ClassType MEMORY_REPOSITORY_CUSTODIAN<ClassType>::SearchElement(ClassType ElementToSearchBy)
{
    for (auto& classItem : this->TasksVector)
        if (classItem == ElementToSearchBy)
            return classItem;
    return ElementToSearchBy;
}

template<typename ClassType>
vector<ClassType> MEMORY_REPOSITORY_CUSTODIAN<ClassType>::GetVector()
{
    return this->TasksVector;
}

template<typename ClassType>
int MEMORY_REPOSITORY_CUSTODIAN<ClassType>::GetIndex()
{
    return this->Index;
}

template<typename ClassType>
void MEMORY_REPOSITORY_CUSTODIAN<ClassType>::SetIndex(int NewIndex)
{
    this->Index = NewIndex;
}

// FILE REPOSITORY

template<typename ClassType>
vector<ClassType> FILE_REPOSITORY_CUSTODIAN<ClassType>::ReadVector()
{
    ifstream ReadStream(this->FileLocation);
    vector<ClassType> vectorFromInput;
    ClassType currentObject;
    while (ReadStream >> currentObject)
        vectorFromInput.push_back(currentObject);
    return vectorFromInput;
}

template<typename ClassType>
void FILE_REPOSITORY_CUSTODIAN<ClassType>::WriteVector(vector<ClassType>vectorToOutput)
{
    ofstream WriteStream(this->FileLocation);
    for (auto object : vectorToOutput)
        WriteStream << object;
}

template<typename ClassType>
void FILE_REPOSITORY_CUSTODIAN<ClassType>::AddElement(ClassType NewElement)
{
    vector<ClassType> vectorFromInput;
    vectorFromInput = this->ReadVector();
    for (auto currentObject : vectorFromInput)
        if (currentObject == NewElement)
            throw REPOSITORY_ERROR("Element already present in the list!\n\n");
    vectorFromInput.push_back(NewElement);
    this->WriteVector(vectorFromInput);
}

template<typename ClassType>
void FILE_REPOSITORY_CUSTODIAN<ClassType>::DeleteElement(ClassType ElementToDelete)
{
    vector<ClassType> vectorFromInput;
    vectorFromInput = this->ReadVector();
    int currentIndex = 0;
    for (auto currentObject : vectorFromInput)
    {
        if (currentObject == ElementToDelete)
        {
            vectorFromInput.erase(vectorFromInput.begin() + currentIndex);
            this->WriteVector(vectorFromInput);
            return;
        }
        currentIndex++;
    }
    throw REPOSITORY_ERROR("Element not found in the list!\n\n");
}

template<typename ClassType>
void FILE_REPOSITORY_CUSTODIAN<ClassType>::UpdateElement(ClassType UpdatedElement)
{
    vector<ClassType> vectorFromInput;
    vectorFromInput = this->ReadVector();
    for (auto& currentObject : vectorFromInput)
        if (currentObject == UpdatedElement)
        {
            currentObject = UpdatedElement;
            this->WriteVector(vectorFromInput);
            return;
        }
    throw REPOSITORY_ERROR("Element not found in the list!\n\n");
}

template<typename ClassType>
ClassType FILE_REPOSITORY_CUSTODIAN<ClassType>::SearchElement(ClassType ElementToSearchBy)
{
    vector<ClassType> vectorFromInput;
    vectorFromInput = this->ReadVector();
    for (auto currentObject : vectorFromInput)
        if (currentObject == ElementToSearchBy)
            return currentObject;
    return ElementToSearchBy;
}

template<typename ClassType>
vector<ClassType> FILE_REPOSITORY_CUSTODIAN<ClassType>::GetVector()
{
    return this->ReadVector();
}

template<typename ClassType>
void FILE_REPOSITORY_CUSTODIAN<ClassType>::SetFileLocation(string FileLocation)
{
    this->FileLocation = FileLocation;
}

template<typename ClassType>
int FILE_REPOSITORY_CUSTODIAN<ClassType>::GetIndex()
{
    return this->Index;
}

template<typename ClassType>
void FILE_REPOSITORY_CUSTODIAN<ClassType>::SetIndex(int NewIndex)
{
    this->Index = NewIndex;
}

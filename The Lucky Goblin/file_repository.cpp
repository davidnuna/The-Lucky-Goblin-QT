#pragma once

#include "file_repository.h"

template<typename ClassType>
void SERVANT_REPOSITORY<ClassType>::SaveElement (ClassType NewElement)
{
    vector<ClassType> servantVector = this->ReadFromFile();
    for (auto currentObject : servantVector)
        if (currentObject == NewElement)
            throw REPOSITORY_ERROR("Element already present in the list!\n\n");

    servantVector.push_back(NewElement);
    this->WriteToFile(servantVector);
}

template<typename ClassType>
void SERVANT_REPOSITORY<ClassType>::UnsaveElement(ClassType DeletedElement)
{
    vector<ClassType> servantVector = this->ReadFromFile();
    int currentIndex = 0;
    for (auto& classItem : servantVector)
    {
        if (classItem == DeletedElement)
        {
            servantVector.erase(servantVector.begin() + currentIndex);
            this->WriteToFile(servantVector);
            return;
        }
        currentIndex++;
    }
    throw REPOSITORY_ERROR("Element not found in the list!\n\n");
}

template<typename ClassType>
void SERVANT_REPOSITORY<ClassType>::SetFileLocation(string FileLocation)
{
    this->FileLocation = FileLocation;
}

template<typename ClassType>
vector<ClassType> SERVANT_REPOSITORY<ClassType>::GetVector()
{
    return this->ReadFromFile();
}

template<typename ClassType>
string SERVANT_REPOSITORY<ClassType>::GetFileLocation()
{
    return this->FileLocation;
}

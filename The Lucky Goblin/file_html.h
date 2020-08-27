#pragma once
#include "file_repository.h"

template<typename ClassType>
class SERVANT_REPOSITORY_HTML : public SERVANT_REPOSITORY<ClassType>
{
private:
    vector<ClassType> ReadFromFile() override;
    void WriteToFile(vector<ClassType> vectorToWrite) override;
public:
    SERVANT_REPOSITORY_HTML() { this->SetFileLocation("tasks.html"); }
    void Display() override;
};
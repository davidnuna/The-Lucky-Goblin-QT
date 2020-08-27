#pragma once
#include "file_repository.h"

template<typename ClassType>
class SERVANT_REPOSITORY_CSV : public SERVANT_REPOSITORY<ClassType>
{
private:
    vector<ClassType> ReadFromFile() override;
    void WriteToFile(vector<ClassType> vectorToWrite) override;
public:
    SERVANT_REPOSITORY_CSV() { this->SetFileLocation("tasks.csv"); }
    void Display() override;
};
#include "file_csv.h"

template<typename ClassType>
inline vector<ClassType> SERVANT_REPOSITORY_CSV<ClassType>::ReadFromFile()
{
    cout << "1. " << this->FileLocation << endl;
    ifstream ReadStream(this->FileLocation);
    vector<ClassType> vectorFromInput;
    ClassType currentObject;
    while (ReadStream >> currentObject)
        vectorFromInput.push_back(currentObject);
    return vectorFromInput;
}

template<typename ClassType>
void SERVANT_REPOSITORY_CSV<ClassType>::WriteToFile(vector<ClassType> vectorToWrite)
{
    cout << "2. " << this->FileLocation << endl;
    ofstream WriteStream(this->FileLocation);
    for (auto object : vectorToWrite)
        WriteStream << object;
}

template<typename ClassType>
void SERVANT_REPOSITORY_CSV<ClassType>::Display()
{
    string command = "start excel \"" + this->FileLocation + "\"";
    system(command.c_str());
}
#include "file_html.h"

template<typename ClassType>
inline vector<ClassType> SERVANT_REPOSITORY_HTML<ClassType>::ReadFromFile()
{
    ifstream ReadStream(this->FileLocation);
    vector<ClassType> vectorFromInput;
    ClassType currentObject;
    while (ReadHTML(ReadStream, currentObject))
        vectorFromInput.push_back(currentObject);

    //for (auto& currentObject: vectorFromInput)
        //cout << currentObject.GetTitle() << ", " << currentObject.GetType() << ", " << currentObject.GetLastPerformed().GetMonth() << "-" << currentObject.GetLastPerformed().GetDay() << "-" << currentObject.GetLastPerformed().GetYear() << ", " << currentObject.GetTimesPerformed() << ", " << currentObject.GetVision() << endl;

    return vectorFromInput;
}

template<typename ClassType>
void SERVANT_REPOSITORY_HTML<ClassType>::WriteToFile(vector<ClassType> vectorToWrite)
{
    ofstream WriteStream(this->FileLocation);
    WriteStream << "<!DOCTYPE html>" << endl;
    WriteStream << "<html>" << endl;
    WriteStream << "\t<head>" << endl;
    WriteStream << "\t\t<title>Enchantments</title>" << endl;
    WriteStream << "\t</head>" << endl;
    WriteStream << "\t<body>" << endl;
    WriteStream << "\t<table border=\"1\">" << endl;

    for (auto object : vectorToWrite)
        WriteHTML(WriteStream, object);

    WriteStream << "\t</table>" << endl;
    WriteStream << "\t</body>" << endl;
    WriteStream << "</html>";
}

template<typename ClassType>
void SERVANT_REPOSITORY_HTML<ClassType>::Display()
{
    string command = "start chrome \"" + this->FileLocation + "\"";
    system(command.c_str());
}

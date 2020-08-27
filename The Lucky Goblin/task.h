#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "date.h"

using namespace std;

class TASK
{
private:
    string Title;
    string Type;
    MYDATE LastPerformed;
    int TimesPerformed;
    string Vision;

public:
    TASK();
    TASK(string Title, string Type, MYDATE LastPerformed, int TimesPerformed, string Vision);
    string GetTitle();
    string GetType();
    MYDATE GetLastPerformed();
    string GetLastPerformedAsString();
    int GetTimesPerformed();
    string GetVision();
    void SetAllArguments(string Title, string Type, MYDATE LastPerformed, int TimesPerformed, string Vision);
    bool operator==(const TASK& OtherDynamicVector);
    friend istream& operator>>(istream& InFileStream, TASK& Task);
    friend ostream& operator<<(ostream& OutFileStream, TASK Task);
    friend int ReadHTML(istream& InFileStream, TASK& Task);
    friend int WriteHTML(ostream& OutFileStream, TASK Task);
};
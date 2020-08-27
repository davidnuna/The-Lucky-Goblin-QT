#pragma once
#include <string>

using namespace std;

class MYDATE
{
private:
    int Day;
    int Month;
    int Year;
public:
    MYDATE();
    MYDATE(int Day, int Month, int Year);
    int GetDay();
    int GetMonth();
    int GetYear();
    string ToString();
};
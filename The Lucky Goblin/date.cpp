#include "date.h"

MYDATE::MYDATE()
{
    this->Day = 1;
    this->Month = 1;
    this->Year = 1999;
}
MYDATE::MYDATE(int Day, int Month, int Year)
{
    this->Day = Day;
    this->Month = Month;
    this->Year = Year;
}

int MYDATE::GetDay()
{
    return this->Day;
}

int MYDATE::GetMonth()
{
    return this->Month;
}

int MYDATE::GetYear()
{
    return this->Year;
}

string MYDATE::ToString()
{
    string month = to_string(this->Month);
    if (month.size() == 1)
        month.insert(0, "0");
    string day = to_string(this->Day);
    if (day.size() == 1)
        day.insert(0, "0");
    string year = to_string(this->Year);
    while (year.size() != 4)
        year.insert(0, "0");
    return month + "-" + day + "-" + year;
}

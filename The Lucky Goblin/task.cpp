#include "task.h"

TASK::TASK()
{
    MYDATE emptyDate;
    this->Title = "none";
    this->Type = "none";
    this->LastPerformed = emptyDate;
    this->TimesPerformed = 0;
    this->Vision = "none";
}
TASK::TASK(string Title, string Type, MYDATE LastPerformed, int TimesPerformed, string Vision)
{
    this->Title = Title;
    this->Type = Type;
    this->LastPerformed = LastPerformed;
    this->TimesPerformed = TimesPerformed;
    this->Vision = Vision;
}

string TASK::GetTitle()
{
    return this->Title;
}

string TASK::GetType()
{
    return this->Type;
}

MYDATE TASK::GetLastPerformed()
{
    return this->LastPerformed;
}

string TASK::GetLastPerformedAsString()
{
    string month = to_string(this->LastPerformed.GetMonth());
    if (month.size() == 1)
        month.insert(0, "0");
    string day = to_string(this->LastPerformed.GetDay());
    if (day.size() == 1)
        day.insert(0, "0");
    string year = to_string(this->LastPerformed.GetYear());
    while (year.size() != 4)
        year.insert(0, "0");

    return month + "-" + day + "-" + year;
}

int TASK::GetTimesPerformed()
{
    return this->TimesPerformed;
}

string TASK::GetVision()
{
    return this->Vision;
}

void TASK::SetAllArguments(string Title, string Type, MYDATE LastPerformed, int TimesPerformed, string Vision)
{
    this->Title = Title;
    this->Type = Type;
    this->LastPerformed = LastPerformed;
    this->TimesPerformed = TimesPerformed;
    this->Vision = Vision;
}

bool TASK::operator==(const TASK& OtherDynamicVector)
{
    return (this->Title == OtherDynamicVector.Title);
}

istream& operator>>(istream& InFileStream, TASK& Task)
{
    string currentLine;
    string currentToken;
    vector<string>lineTokens;
    getline(InFileStream, currentLine);
    stringstream lineStringStream(currentLine);
    while (getline(lineStringStream, currentToken, ','))
        lineTokens.push_back(currentToken);
    if (lineTokens.size() == 0)
        return InFileStream;

    string TaskTitle = lineTokens.at(0);
    string TaskType = lineTokens.at(1);
    string TaskLastPerformed = lineTokens.at(2);
    int LastPerformedMonth = stoi(TaskLastPerformed.substr(0, 2));
    int LastPerformedDay = stoi(TaskLastPerformed.substr(3, 2));
    int LastPerformedYear = stoi(TaskLastPerformed.substr(6, 4));
    MYDATE LastPerformedDate(LastPerformedDay, LastPerformedMonth, LastPerformedYear);
    int TaskTimesPerformed = stoi(lineTokens.at(3));
    string TaskVision = lineTokens.at(4);
    Task.SetAllArguments(TaskTitle, TaskType, LastPerformedDate, TaskTimesPerformed, TaskVision);

    return InFileStream;
}

ostream& operator<<(ostream& OutFileStream, TASK Task)
{
    string month = to_string(Task.GetLastPerformed().GetMonth());
    if (month.size() == 1)
        month.insert(0, "0");
    string day = to_string(Task.GetLastPerformed().GetDay());
    if (day.size() == 1)
        day.insert(0, "0");
    string year = to_string(Task.GetLastPerformed().GetYear());
    while (year.size() != 4)
        year.insert(0, "0");
    string dateAsString = month + "-" + day + "-" + year;
    string taskMembersAsString = Task.GetTitle() + "," + Task.GetType() + "," + dateAsString + "," + to_string(Task.GetTimesPerformed()) + "," + Task.GetVision();
    OutFileStream << taskMembersAsString << endl;
    return OutFileStream;
}

int ReadHTML(istream& InFileStream, TASK& Task)
{
    string taskTitle, taskType, taskLastPerformed, taskVision;

    string currentLine;
    while (getline(InFileStream, currentLine))
    {
        currentLine.erase(remove(currentLine.begin(), currentLine.end(), '\t'), currentLine.end());
        if (currentLine == "<tr>")
        {
            string temporaryString;
            getline(InFileStream, taskTitle);
            taskTitle.erase(remove(taskTitle.begin(), taskTitle.end(), '\t'), taskTitle.end());
            taskTitle.erase(taskTitle.begin(), taskTitle.begin() + 4);
            taskTitle.erase(taskTitle.end() - 5, taskTitle.end());

            getline(InFileStream, taskType);
            taskType.erase(remove(taskType.begin(), taskType.end(), '\t'), taskType.end());
            taskType.erase(taskType.begin(), taskType.begin() + 4);
            taskType.erase(taskType.end() - 5, taskType.end());

            getline(InFileStream, temporaryString);
            temporaryString.erase(remove(temporaryString.begin(), temporaryString.end(), '\t'), temporaryString.end());
            temporaryString.erase(temporaryString.begin(), temporaryString.begin() + 4);
            temporaryString.erase(temporaryString.end() - 5, temporaryString.end());
            int lastPerformedMonth = stoi(temporaryString.substr(0, 2));
            int lastPerformedDay = stoi(temporaryString.substr(3, 2));
            int lastPerformedYear = stoi(temporaryString.substr(6, 4));
            MYDATE lastPerformedDate(lastPerformedDay, lastPerformedMonth, lastPerformedYear);

            getline(InFileStream, temporaryString);
            temporaryString.erase(remove(temporaryString.begin(), temporaryString.end(), '\t'), temporaryString.end());
            temporaryString.erase(temporaryString.begin(), temporaryString.begin() + 4);
            temporaryString.erase(temporaryString.end() - 5, temporaryString.end());
            int taskTimesPerformed = stoi(temporaryString);

            getline(InFileStream, taskVision);
            taskVision.erase(remove(taskVision.begin(), taskVision.end(), '\t'), taskVision.end());
            taskVision.erase(taskVision.begin(), taskVision.begin() + 4);
            taskVision.erase(taskVision.end() - 5, taskVision.end());
            Task.SetAllArguments(taskTitle, taskType, lastPerformedDate, taskTimesPerformed, taskVision);
            return 1;
        }
    }
    return 0;
}
int WriteHTML(ostream& OutFileStream, TASK Task)
{
    OutFileStream << "\t<tr>" << endl;
    string month = to_string(Task.GetLastPerformed().GetMonth());
    if (month.size() == 1)
        month.insert(0, "0");
    string day = to_string(Task.GetLastPerformed().GetDay());
    if (day.size() == 1)
        day.insert(0, "0");
    string year = to_string(Task.GetLastPerformed().GetYear());
    while (year.size() != 4)
        year.insert(0, "0");
    string dateAsString = month + "-" + day + "-" + year;
    string taskMembersAsString = Task.GetTitle() + "," + Task.GetType() + "," + dateAsString + "," + to_string(Task.GetTimesPerformed()) + "," + Task.GetVision();

    OutFileStream << "\t\t<td>" + Task.GetTitle() + "</td>" << endl;
    OutFileStream << "\t\t<td>" + Task.GetType() + "</td>" << endl;
    OutFileStream << "\t\t<td>" + dateAsString + "</td>" << endl;
    OutFileStream << "\t\t<td>" + to_string(Task.GetTimesPerformed()) + "</td>" << endl;
    OutFileStream << "\t\t<td>" + Task.GetVision() + "</td>" << endl;

    OutFileStream << "\t</tr>" << endl;
    return 0;
}
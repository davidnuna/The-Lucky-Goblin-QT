#pragma once
#include "repository.h"
#include "repository.cpp"
#include "file_repository.h"
#include "file_repository.cpp"
#include "file_csv.h"
#include "file_csv.cpp"
#include "file_html.h"
#include "file_html.cpp"
#include "validation.h"
#include "action.h"
#include "task.h"

class SERVICE
{
    friend class TasksListView;
private:
    shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> CustodianRepository;
    shared_ptr<SERVANT_REPOSITORY<TASK>> ServantRepository;
    VALIDATOR Validator;
    vector<unique_ptr<Action>> undoStackCustodian;
    vector<unique_ptr<Action>> redoStackCustodian;
    vector<unique_ptr<Action>> undoStackServant;
    vector<unique_ptr<Action>> redoStackServant;

public:
    SERVICE() = default;
    SERVICE(shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> RepositoryCustodian, shared_ptr<SERVANT_REPOSITORY<TASK>> RepositoryServant, VALIDATOR Validator);
    void AddTask(string Title, string Type, string LastPerformed, int TimesPerformed, string Vision);
    void UpdateTask(string Title, string Type, string LastPerformed, int TimesPerformed, string Vision);
    void DeleteTask(string Title, string Type, string LastPerformed, int TimesPerformed, string Vision);
    TASK NextTask();
    void SaveTask(string Title, string Type, string LastPerformed, int TimesPerformed, string Vision);
    vector<TASK> GetFilteredVector(string TypeToSearch, int MaximumTimesPerformed);
    void ChangeFileLocation(string FileLocation);
    void ChangeServantFileLocation(string ServantFileLocation);
    vector<TASK> GetVectorOfTasks();
    vector<TASK> GetVectorOfTasksServant();
    void ResetIndex();
    void DisplayServantRepository();
    string GetMyListLocation();
    void undoActionCustodian();
    void redoActionCustodian();
    void undoActionServant();
    void redoActionServant();
};
#pragma once
#include "service.h"

SERVICE::SERVICE(shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> RepositoryCustodian, shared_ptr<SERVANT_REPOSITORY<TASK>> RepositoryServant, VALIDATOR Validator)
{
    this->CustodianRepository = move(RepositoryCustodian);
    this->ServantRepository = RepositoryServant;
    this->Validator = Validator;
}

void SERVICE::AddTask(string Title, string Type, string LastPerformed, int TimesPerformed, string Vision)
{
    int LastPerformedMonth = stoi(LastPerformed.substr(0, 2));
    int LastPerformedDay = stoi(LastPerformed.substr(3, 2));
    int LastPerformedYear = stoi(LastPerformed.substr(6, 4));

    MYDATE LastPerformedDate(LastPerformedDay, LastPerformedMonth, LastPerformedYear);
    this->Validator.ValidateDate(LastPerformedDate);

    TASK TaskToAdd(Title, Type, LastPerformedDate, TimesPerformed, Vision);

    Add addUndo(TaskToAdd, this->CustodianRepository);
    this->undoStackCustodian.push_back(make_unique<Add>(addUndo));

    this->CustodianRepository->AddElement(TaskToAdd);
}

void SERVICE::UpdateTask(string Title, string Type, string LastPerformed, int TimesPerformed, string Vision)
{
    int LastPerformedMonth = stoi(LastPerformed.substr(0, 2));
    int LastPerformedDay = stoi(LastPerformed.substr(3, 2));
    int LastPerformedYear = stoi(LastPerformed.substr(6, 4));

    MYDATE LastPerformedDate(LastPerformedDay, LastPerformedMonth, LastPerformedYear);
    this->Validator.ValidateDate(LastPerformedDate);

    TASK TaskToUpdate(Title, Type, LastPerformedDate, TimesPerformed, Vision);
    TASK UpdatedTask = this->CustodianRepository->SearchElement(TaskToUpdate);

    this->CustodianRepository->UpdateElement(TaskToUpdate);

    Update updateUndo(UpdatedTask, TaskToUpdate, this->CustodianRepository);
    this->undoStackCustodian.push_back(make_unique<Update>(updateUndo));
}

void SERVICE::DeleteTask(string Title, string Type, string LastPerformed, int TimesPerformed, string Vision)
{
    int LastPerformedMonth = stoi(LastPerformed.substr(0, 2));
    int LastPerformedDay = stoi(LastPerformed.substr(3, 2));
    int LastPerformedYear = stoi(LastPerformed.substr(6, 4));

    MYDATE LastPerformedDate(LastPerformedDay, LastPerformedMonth, LastPerformedYear);
    this->Validator.ValidateDate(LastPerformedDate);

    TASK TaskToDelete(Title, Type, LastPerformedDate, TimesPerformed, Vision);
    TASK DeletedTask = this->CustodianRepository->SearchElement(TaskToDelete);

    this->CustodianRepository->DeleteElement(TaskToDelete);

    Remove removeUndo(DeletedTask, this->CustodianRepository);
    this->undoStackCustodian.push_back(make_unique<Remove>(removeUndo));
}

TASK SERVICE::NextTask()
{
    int currentIndex = this->CustodianRepository->GetIndex();
    if (this->CustodianRepository->GetVector().size() == 0)
        throw VALIDATION_ERROR("The list is empty!\n\n");
    if (currentIndex == this->CustodianRepository->GetVector().size())
    {
        this->ResetIndex();
        currentIndex = 0;
    }
    this->CustodianRepository->SetIndex(currentIndex + 1);
    return this->CustodianRepository->GetVector()[currentIndex];
}

void SERVICE::SaveTask(string Title, string Type, string LastPerformed, int TimesPerformed, string Vision)
{
    if (this->ServantRepository == NULL)
        throw VALIDATION_ERROR("Invalid file for mylist!\n\n");

    int LastPerformedMonth = stoi(LastPerformed.substr(0, 2));
    int LastPerformedDay = stoi(LastPerformed.substr(3, 2));
    int LastPerformedYear = stoi(LastPerformed.substr(6, 4));

    MYDATE LastPerformedDate(LastPerformedDay, LastPerformedMonth, LastPerformedYear);
    this->Validator.ValidateDate(LastPerformedDate);

    TASK taskToSearchBy(Title, Type, LastPerformedDate, TimesPerformed, Vision);
    TASK taskToSave = this->CustodianRepository->SearchElement(taskToSearchBy);
    if (taskToSave.GetType() == taskToSearchBy.GetType())
        throw VALIDATION_ERROR("Element not found in the list!\n\n");

    this->ServantRepository->SaveElement(taskToSave);

    Save saveUndo(taskToSave, this->ServantRepository);
    this->undoStackServant.push_back(make_unique<Save>(saveUndo));
}

vector<TASK> SERVICE::GetFilteredVector(string TypeToSearch, int MaximumTimesPerformed)
{
    vector<TASK> tasksVector = this->CustodianRepository->GetVector();
    vector<TASK> filteredVector(tasksVector.size());
    auto endIterator = copy_if(tasksVector.begin(), tasksVector.end(), filteredVector.begin(), [TypeToSearch, MaximumTimesPerformed](TASK TaskToCheck) {return (TaskToCheck.GetType() == TypeToSearch && TaskToCheck.GetTimesPerformed() <= MaximumTimesPerformed); });
    filteredVector.resize(distance(filteredVector.begin(), endIterator));
    return filteredVector;
}

void SERVICE::ChangeFileLocation(string FileLocation)
{
    this->CustodianRepository->SetFileLocation(FileLocation);
}

void SERVICE::ChangeServantFileLocation(string ServantFileLocation)
{
    if (ServantFileLocation.find(".csv") != string::npos)
    {
        SERVANT_REPOSITORY_CSV<TASK> csvRepository;
        this->ServantRepository = make_shared<SERVANT_REPOSITORY_CSV<TASK>>(csvRepository);
        this->ServantRepository->SetFileLocation(ServantFileLocation);
    }
    else if (ServantFileLocation.find(".html") != string::npos)
    {
        SERVANT_REPOSITORY_HTML<TASK> htmlRepository;
        this->ServantRepository = make_shared<SERVANT_REPOSITORY_HTML<TASK>>(htmlRepository);
        this->ServantRepository->SetFileLocation(ServantFileLocation);
    }
}

vector<TASK> SERVICE::GetVectorOfTasks()
{
    return this->CustodianRepository->GetVector();
}

vector<TASK> SERVICE::GetVectorOfTasksServant()
{
    return this->ServantRepository->GetVector();
}

void SERVICE::ResetIndex()
{
    this->CustodianRepository->SetIndex(0);
}

void SERVICE::DisplayServantRepository()
{
    if (this->ServantRepository == NULL)
        throw VALIDATION_ERROR("Invalid file for mylist!\n\n");
    this->ServantRepository->Display();
}

string SERVICE::GetMyListLocation()
{
    return this->ServantRepository->GetFileLocation();
}

void SERVICE::undoActionCustodian()
{
    if (this->undoStackCustodian.size() == 0)
        throw VALIDATION_ERROR("No action to undo!\n");
    unique_ptr<Action> lastAction = move(this->undoStackCustodian.back());
    this->undoStackCustodian.erase(this->undoStackCustodian.end() - 1);
    lastAction->UndoAction();
    this->redoStackCustodian.push_back(move(lastAction));
}

void SERVICE::redoActionCustodian()
{
    if (this->redoStackCustodian.size() == 0)
        throw VALIDATION_ERROR("No action to redo!\n");
    unique_ptr<Action> lastAction = move(this->redoStackCustodian.back());
    this->redoStackCustodian.erase(this->redoStackCustodian.end() - 1);
    lastAction->RedoAction();
    this->undoStackCustodian.push_back(move(lastAction));
}

void SERVICE::undoActionServant()
{
    if (this->undoStackServant.size() == 0)
        throw VALIDATION_ERROR("No action to undo!\n");
    unique_ptr<Action> lastAction = move(this->undoStackServant.back());
    this->undoStackServant.erase(this->undoStackServant.end() - 1);
    lastAction->UndoAction();
    this->redoStackServant.push_back(move(lastAction));
}

void SERVICE::redoActionServant()
{
    if (this->redoStackServant.size() == 0)
        throw VALIDATION_ERROR("No action to redo!\n");
    unique_ptr<Action> lastAction = move(this->redoStackServant.back());
    this->redoStackServant.erase(this->redoStackServant.end() - 1);
    lastAction->RedoAction();
    this->undoStackServant.push_back(move(lastAction));
}

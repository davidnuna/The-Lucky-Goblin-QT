#pragma once

#include <memory>
#include <iostream>
#include "repository.h"
#include "file_repository.h"
#include "file_repository.cpp"
#include "task.h"

using namespace std;

class Action
{
public:
    virtual ~Action() = default;
    virtual void UndoAction() = 0;
    virtual void RedoAction() = 0;
};

class Add : public Action
{
private:
    TASK task;
    shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> repository;
public:
    Add(const TASK& Task, shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> Repository) : task(Task), repository(Repository) {}
    void UndoAction() override;
    void RedoAction() override;
};

class Remove : public Action
{
private:
    TASK task;
    shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> repository;
public:
    Remove(const TASK& Task, shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> Repository) : task(Task), repository(Repository) {}
    void UndoAction() override;
    void RedoAction() override;
};

class Update : public Action
{
private:
    TASK firstTask;
    TASK secondTask;
    shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> repository;
public:
    Update(const TASK& FirstTask, const TASK& SecondTask, shared_ptr<BASE_REPOSITORY_CUSTODIAN<TASK>> Repository) : firstTask(FirstTask), secondTask(SecondTask), repository(Repository) {}
    void UndoAction() override;
    void RedoAction() override;
};

class Save : public Action
{
private:
    TASK task;
    shared_ptr<SERVANT_REPOSITORY<TASK>> repository;
public:
    Save(const TASK& Task, shared_ptr<SERVANT_REPOSITORY<TASK>> Repository) : task(Task), repository(Repository) {}
    void UndoAction() override;
    void RedoAction() override;
};

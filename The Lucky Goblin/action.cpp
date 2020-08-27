#pragma once

#include "action.h"

// CUSTODIAN ACTIONS

void Add::UndoAction()
{
    this->repository->DeleteElement(this->task);
}

void Remove::UndoAction()
{
    this->repository->AddElement(this->task);
}

void Update::UndoAction()
{
    this->repository->UpdateElement(this->firstTask);
}

void Add::RedoAction()
{
    this->repository->AddElement(this->task);
}

void Remove::RedoAction()
{
    this->repository->DeleteElement(this->task);
}

void Update::RedoAction()
{
    this->repository->UpdateElement(this->secondTask);
}

// SERVANT ACTIONS

void Save::UndoAction()
{
    this->repository->UnsaveElement(this->task);
}

void Save::RedoAction()
{
    this->repository->SaveElement(this->task);
}
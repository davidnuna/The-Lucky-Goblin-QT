#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QShortcut>
#include "ui_TheLuckyGoblin.h"
#include "tasksListView.h"
#include "service.h"

class Goblin : public QMainWindow
{
    Q_OBJECT

public:
    Goblin(SERVICE& Service, QWidget *parent = Q_NULLPTR);

private:
    Ui::GoblinClass ui;
    SERVICE& Service;
    TasksListView* myListWindow;
    void PopulateList();
    void PopulateListCustodian();
    void ConnectSignalsAndSlots();
    int GetSelectedIndex() const;
    int GetSelectedIndexCustodian() const;

    void AddTask();
    void DeleteTask();
    void UpdateTask();
    void NextTask();
    void SaveTask();
    void FilterTasks();
    void OpenTasks();
    void UndoActionCustodian();
    void RedoActionCustodian();
    void UndoActionServant();
    void RedoActionServant();
};

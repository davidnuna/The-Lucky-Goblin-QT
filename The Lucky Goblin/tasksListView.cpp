#pragma once

#include "tasksListView.h"

TasksListView::TasksListView(SERVICE& Service, QWidget* parent) : QMainWindow(parent), Service(Service)
{
    ui.setupUi(this);
    this->setWindowIcon(QIcon("goblinslayer.png"));
    this->setWindowTitle(QString("The Lucky Goblin"));

    this->model = new TasksTableModel(this->Service.ServantRepository); 

    ui.tableView->setModel(this->model);
    ui.tableView->setItemDelegate(new PictureDelegate());
    ui.tableView->resizeColumnsToContents();
    ui.tableView->resizeRowsToContents();
}

void TasksListView::Update()
{
    model->emit layoutChanged();
    ui.tableView->resizeColumnsToContents();
    ui.tableView->resizeRowsToContents();
}

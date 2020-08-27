#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QSortFilterProxyModel>
#include "TasksTableModel.h"
#include "PictureDelegate.h"
#include "ui_TasksListView.h"
#include "service.h"

class TasksListView : public QMainWindow
{
    friend class SERVICE;
    Q_OBJECT

public:
    TasksListView(SERVICE& Service, QWidget* parent = Q_NULLPTR);
    void Update();
private:
    TasksTableModel* model;
    Ui::TasksViewWindow ui;
    SERVICE& Service;
};
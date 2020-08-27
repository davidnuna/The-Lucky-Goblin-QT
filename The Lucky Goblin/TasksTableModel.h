#pragma once

#include <QAbstractTableModel>
#include <QBrush>
#include <QFont>
#include "file_repository.h"
#include "task.h"

class TasksTableModel : public QAbstractTableModel
{
private:
    shared_ptr<SERVANT_REPOSITORY<TASK>> repository;

public: 
    TasksTableModel(shared_ptr<SERVANT_REPOSITORY<TASK>> repository, QObject* parent = NULL);
    ~TasksTableModel() = default;

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
};
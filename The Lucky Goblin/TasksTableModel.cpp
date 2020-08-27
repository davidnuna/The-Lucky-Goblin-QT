#pragma once

#include "TasksTableModel.h"

TasksTableModel::TasksTableModel(shared_ptr<SERVANT_REPOSITORY<TASK>> repository, QObject* parent) : QAbstractTableModel(parent)
{
    this->repository = repository;
}

int TasksTableModel::rowCount(const QModelIndex& parent) const
{
    int tasksNumber = this->repository->GetVector().size();
    return tasksNumber;
}

int TasksTableModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant TasksTableModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    vector<TASK> tasks = this->repository->GetVector();
    if (row == tasks.size())
        return QVariant();

    TASK currentTask = tasks[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(currentTask.GetTitle());
        case 1:
            return QString::fromStdString(currentTask.GetType());
        case 2:
            return QString::fromStdString(currentTask.GetLastPerformedAsString());
        case 3:
            return QString::fromStdString(to_string(currentTask.GetTimesPerformed()));
        case 4:
            return QString::fromStdString(currentTask.GetVision());
        default:
            break;
        }
    }

    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        font.setItalic(false);
        return font;
    }

    if (role == Qt::ForegroundRole)
    {
        if (row % 2 == 1)
            return QBrush(QColor(255, 255, 255));
        else
            return QBrush(QColor(0, 73, 83));
    }

    if (role == Qt::BackgroundRole)
    {
        if (row % 2 == 1)
            return QBrush(QColor(3, 125, 80));
    }

    return QVariant();
}

QVariant TasksTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Title");
            case 1:
                return QString("Type");
            case 2:
                return QString("Last Performed");
            case 3:
                return QString("Times Performed");
            case 4:
                return QString("Vision");
            default:
                break;
            }
        }
    }

    if (role == Qt::BackgroundRole)
    {
        return QBrush(QColor(3, 125, 80));
    }

    if (role == Qt::FontRole)
    {
        QFont font("Verdana", 13, 10, true);
        font.setItalic(false);
        font.setBold(true);
        return font;
    }

    if (role == Qt::ForegroundRole)
    {
        return QBrush(QColor(0, 73, 83));
    }

    return QVariant();
}

Qt::ItemFlags TasksTableModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
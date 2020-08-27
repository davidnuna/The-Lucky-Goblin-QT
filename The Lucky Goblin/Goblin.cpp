#pragma once

#include "Goblin.h"

Goblin::Goblin(SERVICE& Service, QWidget *parent)
    : QMainWindow(parent), Service(Service)
{
    ui.setupUi(this);
    this->setWindowIcon(QIcon("goblinslayer.png"));
    this->setWindowTitle(QString("The Lucky Goblin"));

    myListWindow = new TasksListView(Service);

    this->PopulateList();
    this->PopulateListCustodian();
    this->ConnectSignalsAndSlots();
}

void Goblin::PopulateList()
{
    this->ui.tasksListWidget->clear();
    vector<TASK> allTasks = this->Service.GetVectorOfTasks();
    for (TASK& Task : allTasks)
        this->ui.tasksListWidget->addItem(QString::fromStdString(Task.GetTitle()));
    //New color
    //this->ui.tasksListWidget->item(2)->setForeground(Qt::red);
    
    //Nold text
    //QFont newFont;
    //newFont.setFamily(QString("Verdana"));
    //newFont.setBold(1);
    //this->ui.tasksListWidget->item(2)->setFont(newFont);

    //New background
    //this->ui.tasksListWidget->item(2)->setBackground(Qt::black);

    //New font
    //this->ui.tasksListWidget->item(2)->setFont(QString("Verdana")); 

    //Sort alphabetically
    //this->ui.tasksListWidget->sortItems(Qt::AscendingOrder);

    //Highlight
    //this->ui.tasksListWidget->item(1)->setSelected(true);
    //this->ui.tasksListWidget->setFocus();
}

void Goblin::PopulateListCustodian()
{
    this->ui.custodianListWidget->clear();
    vector<TASK> allTasks = this->Service.GetVectorOfTasks();
    for (TASK& Task : allTasks)
        this->ui.custodianListWidget->addItem(QString::fromStdString(Task.GetTitle()));
}

void Goblin::ConnectSignalsAndSlots()
{
    QObject::connect(this->ui.tasksListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->GetSelectedIndex();
        if (selectedIndex < 0)
            return;

        TASK taskAtIndex = this->Service.GetVectorOfTasks()[selectedIndex];
        this->ui.titleLineEdit->setText(QString::fromStdString(taskAtIndex.GetTitle()));
        this->ui.typeLineEdit->setText(QString::fromStdString(taskAtIndex.GetType()));
        this->ui.lastPerformedLineEdit->setText(QString::fromStdString(taskAtIndex.GetLastPerformed().ToString()));
        this->ui.timesPerformedLineEdit->setText(QString::fromStdString(to_string(taskAtIndex.GetTimesPerformed())));
        this->ui.visionLineEdit->setText(QString::fromStdString(taskAtIndex.GetVision()));
        });

    QObject::connect(this->ui.custodianListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->GetSelectedIndexCustodian();
        if (selectedIndex < 0)
            return;
        TASK taskAtIndex = this->Service.GetVectorOfTasks()[selectedIndex];
        this->ui.titleLineEditServant->setText(QString::fromStdString(taskAtIndex.GetTitle()));
        this->ui.typeLineEditServant->setText(QString::fromStdString(taskAtIndex.GetType()));
        this->ui.lastPerformedLineEditServant->setText(QString::fromStdString(taskAtIndex.GetLastPerformed().ToString()));
        this->ui.timesPerformedLineEditServant->setText(QString::fromStdString(to_string(taskAtIndex.GetTimesPerformed())));
        this->ui.visionLineEditServant->setText(QString::fromStdString(taskAtIndex.GetVision()));
        });

    QObject::connect(this->ui.AddButton, &QPushButton::clicked, this, &Goblin::AddTask);
    QObject::connect(this->ui.DeleteButton, &QPushButton::clicked, this, &Goblin::DeleteTask);
    QObject::connect(this->ui.UpdateButton, &QPushButton::clicked, this, &Goblin::UpdateTask);
    QObject::connect(this->ui.ExitButton, &QPushButton::clicked, this, []() { exit(1); });

    QObject::connect(this->ui.NextButton, &QPushButton::clicked, this, &Goblin::NextTask);
    QObject::connect(this->ui.SaveButton, &QPushButton::clicked, this, &Goblin::SaveTask);
    QObject::connect(this->ui.FilterButton, &QPushButton::clicked, this, &Goblin::FilterTasks);
    QObject::connect(this->ui.OpenButton, &QPushButton::clicked, this, &Goblin::OpenTasks);
    QObject::connect(this->ui.ExitButtonServant, &QPushButton::clicked, this, []() {exit(1); });

    QObject::connect(this->ui.tabWidget, &QTabWidget::currentChanged, this, &Goblin::PopulateListCustodian);
    QObject::connect(this->ui.tabWidget, &QTabWidget::currentChanged, [this]() {
        this->ui.filteredListWidget->clear(); 
        });

    QObject::connect(this->ui.UndoButton, &QPushButton::clicked, this, &Goblin::UndoActionCustodian);
    QObject::connect(this->ui.RedoButton, &QPushButton::clicked, this, &Goblin::RedoActionCustodian);

    QShortcut* shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), this);
    QObject::connect(shortcutUndo, &QShortcut::activated, this, &Goblin::UndoActionCustodian);

    QShortcut* shortcutRedoCustodian = new QShortcut(QKeySequence("Ctrl+Y"), this);
    QObject::connect(shortcutRedoCustodian, &QShortcut::activated, this, &Goblin::RedoActionCustodian);

    QObject::connect(this->ui.UndoButtonServant, &QPushButton::clicked, this, &Goblin::UndoActionServant);
    QObject::connect(this->ui.RedoButtonServant, &QPushButton::clicked, this, &Goblin::RedoActionServant);

    QShortcut* shortcutUndoServant = new QShortcut(QKeySequence("Ctrl+X"), this);
    QObject::connect(shortcutUndoServant, &QShortcut::activated, this, &Goblin::UndoActionServant);

    QShortcut* shortcutRedoServant = new QShortcut(QKeySequence("Ctrl+U"), this);
    QObject::connect(shortcutRedoServant, &QShortcut::activated, this, &Goblin::RedoActionServant);
}

int Goblin::GetSelectedIndex() const
{
    QModelIndexList selectedIndexes = this->ui.tasksListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 0)
    {
        this->ui.titleLineEdit->clear();
        this->ui.typeLineEdit->clear();
        this->ui.lastPerformedLineEdit->clear();
        this->ui.timesPerformedLineEdit->clear();
        this->ui.visionLineEdit->clear();
        return -1;
    }

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;

}

int Goblin::GetSelectedIndexCustodian() const
{
    QModelIndexList selectedIndexes = this->ui.custodianListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 0)
    {
        this->ui.titleLineEditServant->clear();
        this->ui.typeLineEditServant->clear();
        this->ui.lastPerformedLineEditServant->clear();
        this->ui.timesPerformedLineEditServant->clear();
        this->ui.visionLineEditServant->clear();
        return -1;
    }

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void Goblin::AddTask()
{
    string newTitle = this->ui.titleLineEdit->text().toStdString();
    string newType = this->ui.typeLineEdit->text().toStdString();
    string newLastPerformed = this->ui.lastPerformedLineEdit->text().toStdString();
    int newTimesPerformed;
    try
    {
        newTimesPerformed = stoi(this->ui.timesPerformedLineEdit->text().toStdString());
    }
    catch (...)
    {
        QMessageBox::critical(this, "Error", "Invalid times performed !");
        return;
    }
    string newVision = this->ui.visionLineEdit->text().toStdString();
    try
    {
        this->Service.AddTask(newTitle, newType, newLastPerformed, newTimesPerformed, newVision);
        this->PopulateList();
        int lastTask = this->Service.GetVectorOfTasks().size() - 1;
        this->ui.tasksListWidget->setCurrentRow(lastTask);
    }
    catch (VALIDATION_ERROR & errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
    catch (REPOSITORY_ERROR & errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
    catch (...)
    {
        QMessageBox::critical(this, "Error", "The fields cannot be empty!!");
        return;
    }
}

void Goblin::DeleteTask()
{
    int selectedIndex = this->GetSelectedIndex();
    if (selectedIndex < 0)
    {
        QMessageBox::critical(this, "Error", "No task was selected!");
        return;
    }

    TASK taskAtIndex = this->Service.GetVectorOfTasks()[selectedIndex];
    string title = this->ui.titleLineEdit->text().toStdString();
    string type = this->ui.typeLineEdit->text().toStdString();
    string lastPerformed = this->ui.lastPerformedLineEdit->text().toStdString();
    int timesPerformed = stoi(this->ui.timesPerformedLineEdit->text().toStdString());
    string vision = this->ui.visionLineEdit->text().toStdString();
    this->Service.DeleteTask(title, type, lastPerformed, timesPerformed, vision);
    this->PopulateList();

    int lastTask = this->Service.GetVectorOfTasks().size() - 1;
    this->ui.tasksListWidget->setCurrentRow(lastTask);
}

void Goblin::UpdateTask()
{
    string newTitle = this->ui.titleLineEdit->text().toStdString();
    string newType = this->ui.typeLineEdit->text().toStdString();
    string newLastPerformed = this->ui.lastPerformedLineEdit->text().toStdString();
    int newTimesPerformed;
    try
    {
        newTimesPerformed = stoi(this->ui.timesPerformedLineEdit->text().toStdString());
    }
    catch (...)
    {
        QMessageBox::critical(this, "Error", "Invalid times performed !");
        return;
    }
    string newVision = this->ui.visionLineEdit->text().toStdString();

    try
    {
        this->Service.UpdateTask(newTitle, newType, newLastPerformed, newTimesPerformed, newVision);
        this->PopulateList();
        int lastTask = this->Service.GetVectorOfTasks().size() - 1;
        this->ui.tasksListWidget->setCurrentRow(lastTask);
    }
    catch (VALIDATION_ERROR & errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
    catch (REPOSITORY_ERROR & errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
    catch (...)
    {
        QMessageBox::critical(this, "Error", "Unknown error ocurred!");
        return;
    }

    int lastTask = 0;
    for (TASK& Task : this->Service.GetVectorOfTasks())
    {
        if (Task.GetTitle() == newTitle)
            break;
        lastTask++;
    }
    this->ui.tasksListWidget->setCurrentRow(lastTask);
}

void Goblin::NextTask()
{
    int selectedIndex = this->GetSelectedIndexCustodian();
    if (selectedIndex < 0)
    {
        QMessageBox::critical(this, "Error", "No task was selected!");
        return;
    }
    int servantListSize = this->Service.GetVectorOfTasks().size();
    int newIndex = (selectedIndex + 1) % servantListSize;
    this->ui.custodianListWidget->setCurrentRow(newIndex);
}

void Goblin::SaveTask()
{
    string newTitle = this->ui.titleLineEditServant->text().toStdString();
    string newType = this->ui.typeLineEditServant->text().toStdString();
    string newLastPerformed = this->ui.lastPerformedLineEditServant->text().toStdString();
    int newTimesPerformed;
    try
    {
        newTimesPerformed = stoi(this->ui.timesPerformedLineEditServant->text().toStdString());
    }
    catch (...)
    {
        QMessageBox::critical(this, "Error", "Invalid times performed !");
        return;
    }
    string newVision = this->ui.visionLineEditServant->text().toStdString();
    try
    {
        this->Service.SaveTask(newTitle, "----", newLastPerformed, newTimesPerformed, newVision);
        int lastTask = this->Service.GetVectorOfTasksServant().size() - 1;
        myListWindow->Update();
    }
    catch (VALIDATION_ERROR & errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
    catch (REPOSITORY_ERROR & errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
    catch (...)
    {
        QMessageBox::critical(this, "Error", "The fields cannot be empty!!");
        return;
    }
}

void Goblin::FilterTasks()
{
    this->ui.filteredListWidget->clear();
    if (this->Service.GetVectorOfTasks().size() == 0)
        return;
    if (this->ui.typeLineEditServant->text().toStdString() == "" || this->ui.timesPerformedLineEditServant->text().toStdString() == "")
        return;
    vector<TASK> allTasks = this->Service.GetFilteredVector(this->ui.typeLineEditServant->text().toStdString(), stoi(this->ui.timesPerformedLineEditServant->text().toStdString()));
    for (TASK& Task : allTasks)
        this->ui.filteredListWidget->addItem(QString::fromStdString(Task.GetTitle()));
}

void Goblin::OpenTasks()
{
    myListWindow->show();
}

void Goblin::UndoActionCustodian()
{
    try
    {
        this->Service.undoActionCustodian();
        this->PopulateList();
    }
    catch (VALIDATION_ERROR& errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
    catch (REPOSITORY_ERROR& errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
}

void Goblin::RedoActionCustodian()
{
    try
    {
        this->Service.redoActionCustodian();
        this->PopulateList();
    }
    catch (VALIDATION_ERROR& errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
}

void Goblin::UndoActionServant()
{
    try
    {
        this->Service.undoActionServant();
        myListWindow->Update();
    }
    catch (VALIDATION_ERROR & errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
}

void Goblin::RedoActionServant()
{
    try
    {
        this->Service.redoActionServant();
        myListWindow->Update();
    }
    catch (VALIDATION_ERROR & errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage.what());
    }
}

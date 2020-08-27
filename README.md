# The-Lucky-Goblin-QT
Simple GUI application for storing and managing tasks for an inn.

# What it does
There are 2 available modes
- custodian
- servant

There are also 3 available files to store the tasks chosen by the servant
- csv
- html
- sql

These options can be changed in the configuration.txt file.

The custion has the following options
- adding a task done by inserting a tasks features in each corresponding field.
- deleting a task done by selecting a task from the list and pressing the DELETE button.
- updating a task done by selecting a task, modifying one of its fields and then pressing the UPDATE button.
- undoingredoing a previous action done by simply pressing the UNDOREDO button.

The servant has the following options
- saving a task done by selecting a task from the custodian's list and pressing the save button. This makes a copy of the original task and adds it in the servant's personal list.
- filtering the tasks done by adding values in the TYPE and TIMES PERFORMED fields. This will show in the FILTERED LIST only the tasks performed at least the number given in the TIMES PERFORMED field and with a type corresponding to the substring in the TYPE substring.
- opening the tasks in a table view done simply by pressing the OPEN button.
- undoingredoing a previous action done by simply pressing the UNDOREDO button.

# Requirements
In order to run the application the QT package and Visual Studio must be installed.

# Usage

1. Start Visual Studio and select "Clone or check out code".
2. In the Repository location field insert "https://github.com/neutralove/The-Lucky-Goblin-QT.git" .
3. Choose a local path.
4. Press "Clone" and you are done.

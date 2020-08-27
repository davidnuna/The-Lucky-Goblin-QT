#include "Goblin.h"
#include <QtWidgets/QApplication>
#include "repository.h"
#include "file_repository.h"
#include "validation.h"
#include "service.h"
#include <memory>

using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MEMORY_REPOSITORY_CUSTODIAN<TASK> memoryRepository;
    FILE_REPOSITORY_CUSTODIAN<TASK> fileRepository;
    SERVANT_REPOSITORY_CSV<TASK> csvRepository;
    SERVANT_REPOSITORY_HTML<TASK> htmlRepository;
    VALIDATOR usedValidator;
    
    ifstream readConfiguration("configuration.txt");
    string custodianRepositoryType;
    string servantRepositoryType;
    getline(readConfiguration, custodianRepositoryType);
    getline(readConfiguration, servantRepositoryType);
    if (custodianRepositoryType == "CustodianRepo: file" && servantRepositoryType == "ServantRepo: csv")
    {
        SERVICE usedService(make_shared<FILE_REPOSITORY_CUSTODIAN<TASK>>(fileRepository), make_shared<SERVANT_REPOSITORY_CSV<TASK>>(csvRepository), usedValidator);
        Goblin GUI(usedService);
        GUI.show();
        a.exec();
    }
    else if (custodianRepositoryType == "CustodianRepo: file" && servantRepositoryType == "ServantRepo: html")
    {
        SERVICE usedService(make_shared<FILE_REPOSITORY_CUSTODIAN<TASK>>(fileRepository), make_shared<SERVANT_REPOSITORY_HTML<TASK>>(htmlRepository), usedValidator);
        Goblin GUI(usedService);
        GUI.show();
        a.exec();
    }
    else if (custodianRepositoryType == "CustodianRepo: inmemory" && servantRepositoryType == "ServantRepo: csv")
    {
        SERVICE usedService(make_shared<MEMORY_REPOSITORY_CUSTODIAN<TASK>>(memoryRepository), make_shared<SERVANT_REPOSITORY_CSV<TASK>>(csvRepository), usedValidator);
        Goblin GUI(usedService);
        GUI.show();
        a.exec();
    }
    else if (custodianRepositoryType == "CustodianRepo: inmemory" && servantRepositoryType == "ServantRepo: html")
    {
        SERVICE usedService(make_shared<MEMORY_REPOSITORY_CUSTODIAN<TASK>>(memoryRepository), make_shared<SERVANT_REPOSITORY_HTML<TASK>>(htmlRepository), usedValidator);
        Goblin GUI(usedService);
        GUI.show();
        a.exec();
    }
    else
    {
        return -1;
    }
    return 0;
}
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QDebug>
#include <QMutex>


class DatabaseManager
{
public:
    static DatabaseManager& instance();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager operator= (const DatabaseManager&) = delete;

    // методы подключения/отключения/проверки к БД
    bool openConnection();
    void closeConnection();
    bool isOpen();

};




#endif // DATABASEMANAGER_H

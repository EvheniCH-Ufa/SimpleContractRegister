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

    // Получение соединения
    QSqlDatabase database();

    // Выполнение запросов
    bool executeQuery(const QString &query);
    QSqlQuery executeSelectQuery(const QString &query);
    QSqlError getLastError()const;

    // Транзакции
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

private:
    DatabaseManager();
    ~DatabaseManager();

    static DatabaseManager *m_instance;
    static QMutex m_mutex;

    QSqlDatabase m_database;
    bool m_isConnected;

};

#endif // DATABASEMANAGER_H

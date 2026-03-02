#include "DatabaseManager.h"

DatabaseManager* DatabaseManager::m_instance = nullptr;
QMutex DatabaseManager::m_mutex;

DatabaseManager::DatabaseManager()
    : m_isConnected(false)
{
}

DatabaseManager::~DatabaseManager()
{
    closeConnection();
}

DatabaseManager &DatabaseManager::instance()
{
    QMutexLocker locker(&m_mutex);
    if (!m_instance)
    {
        m_instance = new DatabaseManager();
    }
    return *m_instance;
}

bool DatabaseManager::openConnection()
{
    if (m_isConnected)
    {
        return true;
    }

    // Настройка подключения
    m_database = QSqlDatabase::addDatabase("QSQLITE", "main_connection");
    m_database.setDatabaseName("ocp.db");

    // Для MySQL/PostgreSQL:
    // m_db.setHostName("localhost");
    // m_db.setPort(3306);
    // m_db.setUserName("user");
    // m_db.setPassword("password");

    m_isConnected = m_database.open();

    if (!m_isConnected)
    {
        qDebug() << "Ошибка при подключении к БД! " << getLastError().text();
    }
    else
    {
        qDebug() << "Подключение к БД успешно.";
        // Также для SQLite включаем поддержку внешних ключей
        QSqlQuery query(m_database);
        query.exec("PRAGMA foreign_keys = ON;");
    }
    return m_isConnected;
}

void DatabaseManager::closeConnection()
{
    if (!m_isConnected)
    {
        return;
    }

    m_database.close();
    m_isConnected = false;
    qDebug() << "Соединение с БД закрыто.";
}

bool DatabaseManager::isOpen()
{
    return m_isConnected && m_database.isOpen();
}

QSqlDatabase DatabaseManager::database()
{
    return m_database;
}

bool DatabaseManager::executeQuery(const QString &query)
{
    if (!isOpen())
    {
        return false;
    }

    QSqlQuery q(m_database);

    bool is_done = q.exec(query);

    if (!is_done)
    {
        qDebug() << "Ошибка выполнения запроса: " << getLastError().text();
        qDebug() << "Запрос: " << query;
    }

    return  is_done;
}

QSqlQuery DatabaseManager::executeSelectQuery(const QString &query)
{
    QSqlQuery result(m_database);

    if (isOpen())
    {
        result.exec(query);
        if (result.lastError().isValid())
        {
            qDebug() << "Ошибка выполнения Select: " << getLastError().text();
            qDebug() << "Запрос: " << query;
        }
    }

    return  result;
}

QSqlError DatabaseManager::getLastError() const
{
    return m_database.lastError();
}

bool DatabaseManager::beginTransaction()
{
    return m_database.isOpen() ? m_database.transaction() : false;
}

bool DatabaseManager::commitTransaction()
{
    return m_database.isOpen() ? m_database.commit() : false;
}

bool DatabaseManager::rollbackTransaction()
{
    return m_database.isOpen() ? m_database.rollback() : false;
}


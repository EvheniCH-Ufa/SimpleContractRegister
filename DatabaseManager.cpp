#include "DatabaseManager.h"

#include <QMessageBox> // для помощи - удалить

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

bool DatabaseManager::checkTables()
{
    return createContractsTable()
            && createContragentsTable();
}




// BEGIN ================ CRUD операции для Контрагента ========== BEGIN

bool DatabaseManager::createContragentsTable()
{
    if (!isOpen())
    {
        return false;
    }

    QSqlQuery query(m_database);
    const QString tableName = "Contragents";

  //  bool success1 = query.exec(
  //          "DROP TABLE IF EXISTS " + tableName);

    bool success = query.exec(
            "CREATE TABLE IF NOT EXISTS " + tableName + " ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name            TEXT NOT NULL UNIQUE, "
            "address         TEXT,"
            "e_mail          TEXT,"
            "phone           INTEGER,"
            "contact_person  TEXT,"
            "contact_phone   INTEGER,"
            "is_active       INTEGER DEFAULT 1"
            ")");

/*
******************************
*       Contragents          *
******************************
* id (uint)                  *
* name (str)                 *
* address (str)              *
* e_mail (str)               *
* phone (longint)            *
* contactPerson (str)        *
* contactPhone (longint)     *
******************************

*/

    if (success)
    {
        QSqlQuery checkTableQuery( "SELECT COUNT(*) FROM " + tableName, m_database);
        if (checkTableQuery.next() && checkTableQuery.value(0).toInt() == 0) // выборка есть и количество 0
        {
            query.exec("INSERT INTO " + tableName + " (name) VALUES ('One')");
            query.exec("INSERT INTO " + tableName + " (name) VALUES ('Two')");
        }
    }
    return  success;
}

long long DatabaseManager::addContragent(const ContragentData &data)
{
    QSqlQuery query(m_database);
    query.prepare
            (
                "INSERT INTO contragents ( name,  address,  e_mail,  phone,  contact_person,  contact_phone) "
                "VALUES                  (:name, :address, :e_mail, :phone, :contact_person, :contact_phone) "
            );

    query.bindValue(":name", data.name);
    query.bindValue(":address", data.address);
    query.bindValue(":e_mail", data.e_mail);
    query.bindValue(":phone", data.phone);
    query.bindValue(":contact_person", data.contactPerson);
    query.bindValue(":contact_phone", data.contactPhone);

    if (!query.exec())
    {
        qDebug() << "Ошибка добавления:" << query.lastError().text();
        QMessageBox::warning(nullptr, "Ошибка добавления", query.lastError().text());
        return -1;
    }

    // Получить сгенерированный ID
    return query.lastInsertId().toLongLong();
}

bool DatabaseManager::updateContragent(const ContragentData &data)
{
    QSqlQuery query(m_database);
    query.prepare
            (
                "UPDATE contragents SET "
                "name = :name, "
                "address = :address, "
                "e_mail = :e_mail, "
                "phone = :phone, "
                "contact_person = :contact_person, "
                "contact_phone = :contact_phone "
                "WHERE id = :id"
            );

    query.bindValue(":id", data.id);
    query.bindValue(":name", data.name);
    query.bindValue(":address", data.address);
    query.bindValue(":e_mail", data.e_mail);
    query.bindValue(":phone", data.phone);
    query.bindValue(":contact_person", data.contactPerson);
    query.bindValue(":contact_phone", data.contactPhone);

    if (!query.exec())
    {
        qDebug() << "Ошибка обновления:" << query.lastError().text();
        QMessageBox::warning(nullptr, "Ошибка обновления", query.lastError().text());
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DatabaseManager::deleteContragent(int id)
{
    QSqlQuery query(m_database);
    query.prepare
            (
                "UPDATE contragents SET "
                "is_active = 0 "
                "WHERE id = :id"
            );

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Ошибка мягкого удаления:" << query.lastError().text();
        QMessageBox::warning(nullptr, "Ошибка мягкого удаления", query.lastError().text());
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DatabaseManager::restoreContragent(int id)
{
    QSqlQuery query(m_database);
    query.prepare
            (
                "UPDATE contragents SET "
                "is_active = 1 "
                "WHERE id = :id"
            );

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Ошибка мягкого удаления:" << query.lastError().text();
        QMessageBox::warning(nullptr, "Ошибка мягкого удаления", query.lastError().text());
        return false;
    }

    return query.numRowsAffected() > 0;
}
// END ================ CRUD операции для Контрагента ========== END

bool DatabaseManager::createContractsTable()
{
    if (!isOpen())
    {
        return false;
    }

    QSqlQuery query(m_database);
    const QString tableName = "Contracts";

    bool success = query.exec(
            "CREATE TABLE IF NOT EXISTS " + tableName + " ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "number           TEXT NOT NULL UNIQUE, "
            "description      TEXT,"
            "contragent_id    INTEGER DEFAULT 1,"
            "date             DATETIME,"
            "total_cost       REAL,"
            "cost_implem_fact REAL,"
            "cost_implem_docs REAL,"
            "is_active        INTEGER DEFAULT 1"
            ")");

    if (success)
    {
        QSqlQuery checkTableQuery( "SELECT COUNT(*) FROM " + tableName, m_database);
        if (checkTableQuery.next() && checkTableQuery.value(0).toInt() == 0) // выборка есть и количество 0
        {
            query.exec("INSERT INTO " + tableName + " (number) VALUES ('One1')");
            query.exec("INSERT INTO " + tableName + " (number) VALUES ('Two2')");
        }
    }
    return  success;
}




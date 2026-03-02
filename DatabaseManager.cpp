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

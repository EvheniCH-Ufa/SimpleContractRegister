#include "mainwindow.h"
#include "DatabaseManager.h"
#include <QMessageBox>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // connectimsay
    if (!DatabaseManager::instance().openConnection())
    {
        QMessageBox::critical(nullptr, "Ошибка!", "Не удалось подключиться к БД\n"
                              + DatabaseManager::instance().getLastError().text());
        return 1;
    }

    MainWindow w;
    w.show();

    int result = a.exec();

    // close connection
    DatabaseManager::instance().closeConnection();

    return result;
}

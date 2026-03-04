#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QWidget>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    // Слоты для кнопок
    void on_addContract_Bttn_clicked();
    void on_delContract_Bttn_clicked();
    void on_editContract_Bttn_clicked();
    void on_refreshContract_Bttn_clicked();

    // Слоты для фильтрации
    void on_searchEdit_textChanged(const QString &text);
    void on_filterCombo_currentIndexChanged(int index);

    // Слот для выделения
    void on_tableView_clicked(const QModelIndex &index);


private:
    void setupTableView();        // настройка внешнего вида
    void setupProxyModel();       // настройка прокси-модели
    void updateButtonState();     // обновление состояния кнопок

    Ui::MainWindow *ui;

    QSqlTableModel *m_model;             // модель
    QSortFilterProxyModel *m_proxyModel; // прокси для фильтрации
};
#endif // MAINWINDOW_H

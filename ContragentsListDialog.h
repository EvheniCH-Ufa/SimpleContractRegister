#ifndef CONTRAGENTSLISTDIALOG_H
#define CONTRAGENTSLISTDIALOG_H

#include <QDialog>
#include <QMainWindow>

#include <QWidget>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

#include "TableModelClass_Contragents.h"
#include "ContragentDialog.h"

namespace Ui {
class ContragentsListDialog;
}

class ContragentsListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContragentsListDialog(QWidget *parent = nullptr);
    ~ContragentsListDialog();

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

    // Слот для открытия формы нового контрагента
//    void onOpenContragentsList();



    void on_addContragent_Bttn_clicked();

    void on_editContragent_Bttn_clicked();

    void on_refreshContragent_Bttn_clicked();

private:
    Ui::ContragentsListDialog *ui;

    ContragentDialog *m_contragentDialog = nullptr;  // forma novogo kontragenta


    void setupTableView();        // настройка внешнего вида
    void setupProxyModel();       // настройка прокси-модели
    void updateButtonState();     // обновление состояния кнопок

    QSqlTableModel *m_model;             // модель
    QSortFilterProxyModel *m_proxyModel; // прокси для фильтрации



};

#endif // CONTRAGENTSLISTDIALOG_H

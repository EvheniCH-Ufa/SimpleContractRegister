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

enum class FormMode
{
    ModeNormal,
    ModeRestore,
    ModeSelection
};

class ContragentsListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContragentsListDialog(QWidget *parent = nullptr);
    ~ContragentsListDialog();

    FormMode getFormMode() const;
    void setFormMode(const FormMode &formMode);

private slots:
    // Слоты для фильтрации
    void on_searchEdit_textChanged(const QString &text);
    void on_filterCombo_currentIndexChanged(int index);

    // Слот для выделения
    void on_tableView_clicked(const QModelIndex &index);

    // Слот для открытия формы нового контрагента
//    void onOpenContragentsList();

    // Слоты для кнопок
    void on_addContragent_Bttn_clicked();
    void on_editContragent_Bttn_clicked();
    void on_refreshContragent_Bttn_clicked();
    void on_delContragent_Bttn_clicked();

    void on_restoreContragent_Bttn_clicked();

private:
    Ui::ContragentsListDialog *ui;

    ContragentDialog *m_contragentDialog = nullptr;  // forma novogo kontragenta


    void setupTableView();        // настройка внешнего вида
    void setupProxyModel();       // настройка прокси-модели
    void updateButtonState();     // обновление состояния кнопок

    QSqlTableModel *m_model;             // модель
    QSortFilterProxyModel *m_proxyModel; // прокси для фильтрации

    int getSelectedTableRow();
    FormMode m_formMode = FormMode::ModeNormal;

    ContragentData getDataFromSelectedRow(int row);
};

#endif // CONTRAGENTSLISTDIALOG_H

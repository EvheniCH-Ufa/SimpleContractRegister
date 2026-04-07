#ifndef CONTRAGENTDIALOG_H
#define CONTRAGENTDIALOG_H

#include <QDialog>
#include "DatabaseManager.h"

namespace Ui {
class ContragentDialog;
}

class ContragentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContragentDialog(QWidget *parent = nullptr);
    ~ContragentDialog();

    void setData(const ContragentData &data);
    void clearData();

private slots:
    void on_cancel_Bttn_clicked();

    void on_ok_Bttn_clicked();

private:
    Ui::ContragentDialog *ui;

    ContragentData getData();

};

#endif // CONTRAGENTDIALOG_H

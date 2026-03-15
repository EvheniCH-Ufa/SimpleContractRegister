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

    void setData(const contragentData &data);

private slots:
    void on_cancel_Bttn_clicked();

    void on_ok_Bttn_clicked();

private:
    Ui::ContragentDialog *ui;

};

#endif // CONTRAGENTDIALOG_H

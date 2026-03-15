#ifndef CONTRAGENTDIALOG_H
#define CONTRAGENTDIALOG_H

#include <QDialog>

namespace Ui {
class ContragentDialog;
}

class ContragentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContragentDialog(QWidget *parent = nullptr);
    ~ContragentDialog();

private:
    Ui::ContragentDialog *ui;
};

#endif // CONTRAGENTDIALOG_H

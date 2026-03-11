#ifndef CONTRAGENTSLISTDIALOG_H
#define CONTRAGENTSLISTDIALOG_H

#include <QDialog>

namespace Ui {
class ContragentsListDialog;
}

class ContragentsListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContragentsListDialog(QWidget *parent = nullptr);
    ~ContragentsListDialog();

private:
    Ui::ContragentsListDialog *ui;
};

#endif // CONTRAGENTSLISTDIALOG_H

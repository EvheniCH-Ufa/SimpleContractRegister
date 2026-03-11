#include "ContragentsListDialog.h"
#include "ui_ContragentsListDialog.h"

ContragentsListDialog::ContragentsListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContragentsListDialog)
{
    ui->setupUi(this);
}

ContragentsListDialog::~ContragentsListDialog()
{
    delete ui;
}

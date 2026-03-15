#include "ContragentDialog.h"
#include "ui_ContragentDialog.h"

ContragentDialog::ContragentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContragentDialog)
{
    ui->setupUi(this);
}

ContragentDialog::~ContragentDialog()
{
    delete ui;
}

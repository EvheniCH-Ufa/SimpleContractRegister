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

void ContragentDialog::setData(const contragentData &data)
{
    ui->id_Edit->setText(QString::number(data.id));
    ui->name_Edit->setText(data.name);
    ui->address_Edit->setText(data.adress);
    ui->email_Edit->setText(data.e_mail);
    ui->phone_Edit->setText(QString::number(data.phone));
    ui->contactPerson_Edit->setText(data.contactPerson);
    ui->contactPersonPhone_Edit->setText(QString::number(data.contactPhone));
}

void ContragentDialog::on_cancel_Bttn_clicked()
{
    close();
}

void ContragentDialog::on_ok_Bttn_clicked()
{

    close();
}

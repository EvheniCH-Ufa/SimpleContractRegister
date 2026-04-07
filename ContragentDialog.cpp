#include "ContragentDialog.h"
#include "ui_ContragentDialog.h"
#include <QMessageBox>

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

void ContragentDialog::setData(const ContragentData &data)
{
    ui->id_Edit->setText(QString::number(data.id));
    ui->name_Edit->setText(data.name);
    ui->address_Edit->setText(data.address);
    ui->email_Edit->setText(data.e_mail);
    ui->phone_Edit->setText(QString::number(data.phone));
    ui->contactPerson_Edit->setText(data.contactPerson);
    ui->contactPersonPhone_Edit->setText(QString::number(data.contactPhone));
}

void ContragentDialog::clearData()
{
    ui->id_Edit->setText(QString::number(-1));
    ui->name_Edit->clear();
    ui->address_Edit->clear();
    ui->email_Edit->clear();
    ui->phone_Edit->clear();
    ui->contactPerson_Edit->clear();
    ui->contactPersonPhone_Edit->clear();
}

void ContragentDialog::on_cancel_Bttn_clicked()
{
    close();
}

const int ISNEWCONTRAGENT = - 1;
void ContragentDialog::on_ok_Bttn_clicked()
{
    ContragentData data = getData();

    if (ui->id_Edit->text().toInt() == ISNEWCONTRAGENT)
    {
        auto res = DatabaseManager::instance().addContragent(data);
        if (res >= 0)
        {
            accept();
        }
    }
    else
    {
        if (DatabaseManager::instance().updateContragent(data))
        {
            accept();
        }
    }
}

ContragentData ContragentDialog::getData()
{
    ContragentData result;

    result.id = ui->id_Edit->text().toInt();
    result.name = ui->name_Edit->text();
    result.address = ui->address_Edit->text();
    result.e_mail = ui->email_Edit->text();
    result.phone = ui->phone_Edit->text().toLongLong();
    result.contactPerson = ui->contactPerson_Edit->text();
    result.contactPhone = ui->contactPersonPhone_Edit->text().toLongLong();

    return  result;
}

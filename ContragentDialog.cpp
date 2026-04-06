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

void ContragentDialog::setData(const ContragentData &data)
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

const int ISNEWCONTRAGENT = - 1;
void ContragentDialog::on_ok_Bttn_clicked()
{
    ContragentData data = getData();

    if (ui->id_Edit->text().toInt() == ISNEWCONTRAGENT)
    {
        DatabaseManager::instance().addContragent(data);
    }
    else
    {
        DatabaseManager::instance().updateContragent(data);
    }

    accept();
}

ContragentData ContragentDialog::getData()
{
    ContragentData result;

    result.id = ui->id_Edit->text().toInt();
    result.name = ui->name_Edit->text();
    result.adress = ui->address_Edit->text();
    result.e_mail = ui->email_Edit->text();
    result.phone = ui->phone_Edit->text().toLongLong();
    result.contactPerson = ui->contactPerson_Edit->text();
    result.contactPhone = ui->contactPersonPhone_Edit->text().toLongLong();

    return  result;
}

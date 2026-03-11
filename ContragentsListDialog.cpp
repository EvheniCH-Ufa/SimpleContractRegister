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

void ContragentsListDialog::on_delContract_Bttn_clicked()
{

}

void ContragentsListDialog::on_addContract_Bttn_clicked()
{

}

void ContragentsListDialog::on_editContract_Bttn_clicked()
{

}

void ContragentsListDialog::on_refreshContract_Bttn_clicked()
{

}


void ContragentsListDialog::on_searchEdit_textChanged(const QString &text)
{

}

void ContragentsListDialog::on_filterCombo_currentIndexChanged(int index)
{

}


// Слот для выделения
void ContragentsListDialog::on_tableView_clicked(const QModelIndex &index)
{

}

void ContragentsListDialog::setupTableView()
{
    //vydelenie
    ui->contractTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->contractTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->contractTableView->setAlternatingRowColors(true);
    ui->contractTableView->setSortingEnabled(true);

    // width of coluns
    ui->contractTableView->setColumnWidth(0, 160);
    ui->contractTableView->setColumnWidth(1, 60);
    ui->contractTableView->setColumnWidth(2, 60);
    ui->contractTableView->setColumnWidth(3, 60);
    ui->contractTableView->setColumnWidth(4, 60);
    ui->contractTableView->setColumnWidth(5, 60);

    // poslednij - tyanetsya
    ui->contractTableView->horizontalHeader()->setStretchLastSection(true);
    // Скрываем ненужные столбцы (если есть)
    // ui->tableView->setColumnHidden(5, true); // скрыть дату приема

}

void ContragentsListDialog::setupProxyModel()
{

}

void ContragentsListDialog::updateButtonState()
{

}



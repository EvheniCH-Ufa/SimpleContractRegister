#include "ContragentsListDialog.h"
#include "ui_ContragentsListDialog.h"
#include "DatabaseManager.h"


ContragentsListDialog::ContragentsListDialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::ContragentsListDialog)
  , m_model(nullptr)  // сначала nullptr
  , m_proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);


    // sozdanie dialoga novogo kontragenta
//    m_contragentsDialog = new ContragentsListDialog(this);
//    m_contragentsDialog->setWindowTitle("Справочник контрагентов");



    // подключаем модель контрактов
    m_model = new TableModel_Contragents (this, DatabaseManager::instance().database());

    // настраиваем прокси модель
   // m_proxyModel->setSourceModel(m_model);
    ui->contragentTableView->setModel(m_model);

    setupTableView(); // настройка вида таблицы


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
    ui->contragentTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->contragentTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->contragentTableView->setAlternatingRowColors(true);
    ui->contragentTableView->setSortingEnabled(true);

    // width of coluns
    ui->contragentTableView->setColumnWidth(0, 50);     // "ID"
    ui->contragentTableView->setColumnWidth(1, 240);    // "Наименование"
    ui->contragentTableView->setColumnWidth(2, 120);    // "Адрес"
    ui->contragentTableView->setColumnWidth(3, 80);     // "e_mail"
    ui->contragentTableView->setColumnWidth(4, 80);     // "Телефон"
    ui->contragentTableView->setColumnWidth(5, 150);    // "Контактное лицо"
  //  ui->contragentTableView->setColumnWidth(6, 300);  // "Телефон контактного\nлица"

    // poslednij - tyanetsya
    ui->contragentTableView->horizontalHeader()->setStretchLastSection(true);
    // Скрываем ненужные столбцы (если есть)
    // ui->tableView->setColumnHidden(5, true); // скрыть дату приема

}

void ContragentsListDialog::setupProxyModel()
{

}

void ContragentsListDialog::updateButtonState()
{

}



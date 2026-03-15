#include "ContragentsListDialog.h"
#include "ui_ContragentsListDialog.h"
#include "DatabaseManager.h"
#include "QMessageBox"


ContragentsListDialog::ContragentsListDialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::ContragentsListDialog)
  , m_model(nullptr)  // сначала nullptr
  , m_proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);


    // sozdanie dialoga novogo kontragenta
    m_contragentDialog = new ContragentDialog(this);
//    m_contragentDialog->setWindowTitle("Контрагент");

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



void ContragentsListDialog::on_addContragent_Bttn_clicked()
{
   m_contragentDialog->exec();
}

void ContragentsListDialog::on_editContragent_Bttn_clicked()
{
    QModelIndexList selectedRows = ui->contragentTableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty())
    {
        QMessageBox::warning(this, "Внимание", "Выберите контрагента для редактирования");
        return;
    }

    // Берем первую выделенную строку
    QModelIndex index = selectedRows.first();
    int row = index.row();

    contragentData data;
    // Получаем данные из модели
    const auto model = ui->contragentTableView->model();
    data.id            = model->data(model->index(row, 0)).toString().toULongLong();   // колонка с id
    data.name          = model->data(model->index(row, 1)).toString();      // колонка с именем
    data.adress        = model->data(model->index(row, 2)).toString();
    data.e_mail        = model->data(model->index(row, 3)).toString();
    data.phone         = model->data(model->index(row, 4)).toULongLong();
    data.contactPerson = model->data(model->index(row, 5)).toString();
    data.contactPhone  = model->data(model->index(row, 6)).toULongLong();

    m_contragentDialog->setData(data);
    m_contragentDialog->setWindowTitle("Изменение контрагента " + data.name);

    m_contragentDialog->exec();
}

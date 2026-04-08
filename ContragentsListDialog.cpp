#include "ContragentsListDialog.h"
#include "ui_ContragentsListDialog.h"
#include "DatabaseManager.h"
#include <QMessageBox>



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

    // width of columns
    ui->contragentTableView->setColumnWidth(0, 50);     // "ID"
    ui->contragentTableView->setColumnWidth(1, 240);    // "Наименование"
    ui->contragentTableView->setColumnWidth(2, 120);    // "Адрес"
    ui->contragentTableView->setColumnWidth(3, 80);     // "e_mail"
    ui->contragentTableView->setColumnWidth(4, 80);     // "Телефон"
    ui->contragentTableView->setColumnWidth(5, 150);    // "Контактное лицо"
    ui->contragentTableView->setColumnWidth(6, 80);    // "Телефон контактного\nлица"
    //  ui->contragentTableView->setColumnWidth(7, 50); // "Активен"

    // poslednij - tyanetsya
    ui->contragentTableView->horizontalHeader()->setStretchLastSection(true);
    // Скрываем ненужные столбцы (если есть)
    // ui->tableView->setColumnHidden(5, true); // скрыть
}

void ContragentsListDialog::setupProxyModel()
{

}

void ContragentsListDialog::updateButtonState()
{

}

int ContragentsListDialog::getSelectedTableRow()
{
    QModelIndexList selectedRows = ui->contragentTableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty())
    {
        QMessageBox::warning(this, "Внимание", "Выберите контрагента для редактирования");
        return -1;
    }

    // Берем первую выделенную строку
    QModelIndex index = selectedRows.first();
    return index.row();
}

ContragentData ContragentsListDialog::getDataFromSelectedRow(int row)
{
    ContragentData data;
    // Получаем данные из модели
    const auto model = ui->contragentTableView->model();
    data.id            = model->data(model->index(row, 0)).toLongLong();   // колонка с id
    data.name          = model->data(model->index(row, 1)).toString();      // колонка с именем
    data.address       = model->data(model->index(row, 2)).toString();
    data.e_mail        = model->data(model->index(row, 3)).toString();
    data.phone         = model->data(model->index(row, 4)).toULongLong();
    data.contactPerson = model->data(model->index(row, 5)).toString();
    data.contactPhone  = model->data(model->index(row, 6)).toULongLong();

    return  data;
}

void ContragentsListDialog::on_addContragent_Bttn_clicked()
{
    m_contragentDialog->clearData();
    m_contragentDialog->setWindowTitle("Добавление нового контрагента ");

    if (m_contragentDialog->exec() == QDialog::Accepted)
    {
        m_model->select();
        //QMessageBox::warning(this, "Warning", "Neobhodimo obnovit' table!!!");
    }
}

void ContragentsListDialog::on_editContragent_Bttn_clicked()
{
    int row = getSelectedTableRow();
    if (row < 0)
    {
        return;
    }

    ContragentData data = getDataFromSelectedRow(row);
    m_contragentDialog->setData(data);
    m_contragentDialog->setWindowTitle("Изменение контрагента " + data.name);

    if (m_contragentDialog->exec() == QDialog::Accepted)
    {
        m_model->select();
        //QMessageBox::warning(this, "Warning", "Neobhodimo obnovit' table!!!");
    }
}

void ContragentsListDialog::on_refreshContragent_Bttn_clicked()
{
    m_model->select();
}

void ContragentsListDialog::on_delContragent_Bttn_clicked()
{
    int row = getSelectedTableRow();
    if (row < 0)
    {
        return;
    }

    ContragentData data = getDataFromSelectedRow(row);

    DatabaseManager::instance().deleteContragent(data.id);
    m_model->select();
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "DatabaseManager.h"
#include <QHeaderView>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_model(nullptr)  // сначала nullptr
    , m_proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    // sozdaem model
    m_model = new QSqlTableModel(this, DatabaseManager::instance().database());

    // этот блок наверное в контсруктор модели
    m_model->setTable("Contracts");
    m_model->setHeaderData(0, Qt::Horizontal, "ID");
    m_model->setHeaderData(1, Qt::Horizontal, "ID1");
    m_model->setHeaderData(2, Qt::Horizontal, "ID2");
    m_model->select();

    // настраиваем прокси модель
    m_proxyModel->setSourceModel(m_model);
    ui->contractTableView->setModel(m_model);

    setupTableView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTableView()
{
    //vydelenie
    ui->contractTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->contractTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->contractTableView->setAlternatingRowColors(true);
    ui->contractTableView->setSortingEnabled(true);

    // width of coluns
    ui->contractTableView->setColumnWidth(0, 60);
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

void MainWindow::on_addContract_Bttn_clicked()
{
    int row = m_model->rowCount();
    m_model->insertRow(row);

    // Устанавливаем значения по умолчанию
    m_model->setData(m_model->index(row, 1), "Новый");
    m_model->setData(m_model->index(row, 2), "Сотрудник");
    m_model->setData(m_model->index(row, 3), "Без отдела");
    m_model->setData(m_model->index(row, 4), 30000);


}



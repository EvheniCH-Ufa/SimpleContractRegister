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

    // svazka menu "Data-Spravochnik-Kontragent" c metodom
    connect(ui->actionOpenContragentsList, &QAction::triggered, this, &MainWindow::onOpenContragentsList);

    // sozdanie dialoga kontragentov
    m_contragentsDialog = new ContragentsListDialog(this);
    m_contragentsDialog->setWindowTitle("Справочник контрагентов");



    // подключаем модель контрактов
    m_model = new TableModel_Head (this, DatabaseManager::instance().database());

    // настраиваем прокси модель
    m_proxyModel->setSourceModel(m_model);
    ui->contractTableView->setModel(m_model);

    setupTableView(); // настройка вида таблицы
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

void MainWindow::on_addContract_Bttn_clicked()
{
    QMessageBox::warning(this,"Errorапвап", "Failed to add row:");

    int row = m_model->rowCount();
    m_model->insertRow(row);

    // Устанавливаем значения по умолчанию
    m_model->setData(m_model->index(row, 1), "Новый");
    m_model->setData(m_model->index(row, 2), "Сотрудник");
    m_model->setData(m_model->index(row, 3), "Без отдела");
    m_model->setData(m_model->index(row, 4), 30000);

    // save in bd
    if (m_model->submitAll())
    {
        //update proxy-model
        m_proxyModel->invalidate();
        // find new row in proxy-model and selec his
        for (int i = 0; i < m_proxyModel->rowCount(); ++i)
        {
            const int prModData = m_proxyModel->data(m_proxyModel->index(i, 0)).toInt();
            const int   ModData = m_model->data(m_proxyModel->index(i, 0)).toInt();
            if (prModData == ModData)
            {
                ui->contractTableView->selectRow(i);
                break;
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"Error", "Failed to add row: " + m_model->lastError().text());
    }

    //updateButtonState();
}

void MainWindow::on_delContract_Bttn_clicked()
{

}

void MainWindow::on_editContract_Bttn_clicked()
{

}

void MainWindow::on_refreshContract_Bttn_clicked()
{

}

void MainWindow::on_searchEdit_textChanged(const QString &text)
{

}

void MainWindow::on_filterCombo_currentIndexChanged(int index)
{

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

}

void MainWindow::onOpenContragentsList()
{
    // Создаем экземпляр диалога
 //   ContragentsListDialog dialog(this);

    // Устанавливаем заголовок (опционально)
  //  dialog.setWindowTitle("Справочник контрагентов");

    // Если нужно передать какие-то данные в форму
    // dialog.setSomeParameter(value);

    // Открываем модально (ждет закрытия)
    m_contragentsDialog->exec();

    // После закрытия можно получить данные из формы
    // if (dialog.result() == QDialog::Accepted) {
    //     QString data = dialog.getSomeData();
    //     // обработать данные
    // }

}



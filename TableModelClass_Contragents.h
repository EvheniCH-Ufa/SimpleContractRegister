#ifndef CONTRAGENTSTABLEMODELCLASS_H
#define CONTRAGENTSMODELCLASS_H

#include<QSqlTableModel>

class TableModel_Contragents : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit TableModel_Contragents(QObject *parent = nullptr, QSqlDatabase database = QSqlDatabase());

    // Переопределяем для кастомизации отображения
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Специфические методы
    void setDepartmentFilter(int departmentId);
    void searchEmployees(const QString &searchText);

private:
    void initialize();

};




#endif // HEADTABLEMODELCLASS_H

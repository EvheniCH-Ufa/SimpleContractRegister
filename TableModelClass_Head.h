#ifndef HEADTABLEMODELCLASS_H
#define HEADTABLEMODELCLASS_H

#include<QSqlTableModel>

class TableModel_Head : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit TableModel_Head(QObject *parent = nullptr, QSqlDatabase database = QSqlDatabase());

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

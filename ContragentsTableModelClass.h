#ifndef CONTRAGENTSTABLEMODELCLASS_H
#define CONTRAGENTSTABLEMODELCLASS_H

#include<QSqlTableModel>
#include<QSortFilterProxyModel>

class ContragentsTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit ContragentsTableModel(QObject *parent = nullptr, QSqlDatabase database = QSqlDatabase());

    // Переопределяем для кастомизации отображения
// //   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
 //   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Специфические методы
   // void setDepartmentFilter(int departmentId);
  //  void searchEmployees(const QString &searchText);
    void refresh();

private:
    void initialize();

};

class ContragentProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ContragentProxy(QObject *parent = nullptr);

    void setSearchText(const QString &text);
    void setActiveOnly(bool active);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_searchText;
    bool m_activeOnly = false;
};


#endif // CONTRAGENTSTABLEMODELCLASS_H

#include "TableModelClass_Head.h"

TableModel_Head::TableModel_Head(QObject *parent, QSqlDatabase database)
    : QSqlTableModel(parent, database)
{
    initialize();
}

void TableModel_Head::initialize()
{
    setTable("Contracts");
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "ID1");
    setHeaderData(2, Qt::Horizontal, "ID2");
    setEditStrategy(QSqlTableModel::OnFieldChange);
    select();
}

QVariant TableModel_Head::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    // Форматирование данных для отображения
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
            case 0: // номер строки
            {
                return QString("₽ %1").arg(QSqlTableModel::data(index).toDouble(), 0, 'f', 2);
            }
            case 1: // пока просто другое
            {
                return QString("₽ %1").arg(QSqlTableModel::data(index).toDouble(), 0, 'f', 2);
            }
            default: break;
        }
    }
    // Выравнивание
    if (role == Qt::TextAlignmentRole)
    {
        switch (index.column())
        {
            case 0: // номер строки
            {
                return QVariant( Qt::AlignRight | Qt::AlignVCenter);
            }
            case 1: // номер строки
            {
                return Qt::AlignCenter;
            }
            default: break;
        }
    }
    return QSqlTableModel::data(index, role);
}

QVariant TableModel_Head::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
            case 0: return "ID";
            case 1: return "ID1";
            case 2: return "ID2";
            case 3: return "ID3";
            case 4: return "ID4";
            default: break;
        }
    }
    return QSqlTableModel::headerData(section, orientation, role);
}

void TableModel_Head::setDepartmentFilter(int departmentId)
{
    if (departmentId > 0)
    {
        setFilter(QString("department_id = %1").arg(departmentId));
    }
    else
    {
        setFilter("");
    }
    select();
}

void TableModel_Head::searchEmployees(const QString &searchText)
{
    if (searchText.isEmpty())
    {
        setFilter("");
    }
    else
    {
        setFilter(QString("first_name LIKE '%%1%' OR"
                          "last_name LIKE '%%1%' OR"
                          "department LIKE '%%1%'").arg(searchText));
    }
    select();
}


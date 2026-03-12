#include "TableModelClass_Contragents.h"
#include<QMessageBox>

TableModel_Contragents::TableModel_Contragents(QObject *parent, QSqlDatabase database)
    : QSqlTableModel(parent, database)
{    
    initialize();
}

void TableModel_Contragents::initialize()
{
    setTable("Contragents");
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "Наименование");
    setHeaderData(2, Qt::Horizontal, "Адрес");
    setHeaderData(3, Qt::Horizontal, "e_mail");
    setHeaderData(4, Qt::Horizontal, "Телефон");
    setHeaderData(5, Qt::Horizontal, "Контактное лицо");
    setHeaderData(6, Qt::Horizontal, "Телефон контактного\nлица");
    setEditStrategy(QSqlTableModel::OnFieldChange);
    select();


    /*
******************************              |
*       Contragents          *              |
******************************              |
* id (uint)                  *>-------------+
* name (str)                 *
* adress (str)               *
* e_mail (str)               *
* phone (longint)            *
* contactPerson (str)        *
* contactPhone (longint)     *
******************************
*/
}

QVariant TableModel_Contragents::data(const QModelIndex &index, int role) const
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
                return QVariant( Qt::AlignHCenter | Qt::AlignVCenter);
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

QVariant TableModel_Contragents::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
            case 0: return "ID";
        /*    case 1: return "ID1";
            case 2: return "ID2";
            case 3: return "ID3";
            case 4: return "ID4";*/
            default: break;
        }
    }
    return QSqlTableModel::headerData(section, orientation, role);
}

void TableModel_Contragents::setDepartmentFilter(int departmentId)
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

void TableModel_Contragents::searchEmployees(const QString &searchText)
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




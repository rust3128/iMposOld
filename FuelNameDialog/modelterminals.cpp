#include "modelterminals.h"
#include "LoggingCategories/loggingcategories.h"

ModelTerminals::ModelTerminals(QList<TerminalClass> lsTerm ) :
    m_listTerm(lsTerm)
{

}


int ModelTerminals::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_listTerm.size();

}

int ModelTerminals::columnCount(const QModelIndex &parent) const
{
    return m_listTerm.at(0).colParam();
    Q_UNUSED(parent)
}

QVariant ModelTerminals::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) { return QVariant();}
    TerminalClass t = m_listTerm[index.row()];
    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0: return t.isCheced();
        case 1: return t.terminalID();
        case 2: return t.terminalName();
        case 3: return t.regionID();
        case 4: return t.serverName();
        }
        break;
    case Qt::CheckStateRole:
        if(index.column() == 0) {
            return (t.isCheced()) ? Qt::Checked : Qt::Unchecked;
        }
        break;
    default:
        break;
    }
    return QVariant();
}

bool ModelTerminals::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) {return false;}
    TerminalClass t = m_listTerm[index.row()];

    if(role == Qt::EditRole) {
        if(value.toInt() == Qt::Checked){
            t.setIsCheced(false);

        } else {
            t.setIsCheced(true);
        }
        qInfo(logInfo()) << "IS CHECKED" << t.isCheced();
        emit QAbstractTableModel::dataChanged(index,index);
        return true;
    }
    return false;
}

Qt::ItemFlags ModelTerminals::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(index.isValid() && index.column() == 0){
        flags |= Qt::ItemIsUserCheckable;
        flags |= Qt::ItemIsEditable;

    }
    return flags;
}

QVariant ModelTerminals::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole) { return QVariant();}

    if( orientation == Qt::Vertical ) { return section; }

    switch (section) {
    case 0: return "";
    case 1: return "АЗС";
    case 2: return "Адрес";
    case 3: return "Регион";
    case 4: return "Сервер";
    default:
        break;
    }
    return QVariant();
}

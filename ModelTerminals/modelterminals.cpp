#include "ModelTerminals/modelterminals.h"
#include "LoggingCategories/loggingcategories.h"
#include <QColor>

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
        }
        break;
    case Qt::CheckStateRole:
        if(index.column() == 0) {
            return (t.isCheced()) ? Qt::Checked : Qt::Unchecked;
        }
        break;
    case Qt::BackgroundColorRole:
            return (t.isCheced()) ? QColor("#ffffb2") : QColor("#ffffff");
    default:
        break;
    }
    return QVariant();
}

bool ModelTerminals::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)
    if(!index.isValid()) {return false;}

    m_listTerm[index.row()].setIsCheced(value.toBool());
    emit QAbstractTableModel::dataChanged(index,index);
    return true;

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
    default:
        break;
    }
    return QVariant();
}

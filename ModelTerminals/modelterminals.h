#ifndef MODELTERMINALS_H
#define MODELTERMINALS_H
#include "TerminalClass/terminalclass.h"

#include <QObject>
#include <QAbstractTableModel>

class ModelTerminals : public QAbstractTableModel
{
    Q_OBJECT
    QList<TerminalClass> m_listTerm;
public:
    ModelTerminals(QList<TerminalClass> lsTerm);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;



};

#endif // MODELTERMINALS_H

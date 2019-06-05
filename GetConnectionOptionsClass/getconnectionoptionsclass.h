#ifndef GETCONNECTIONOPTIONSCLASS_H
#define GETCONNECTIONOPTIONSCLASS_H

#include "DataBases/databases.h"
#include "LoggingCategories/loggingcategories.h"
#include "passconv.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>

class GetConnectionOptionsClass : public QObject
{
    Q_OBJECT
public:
    explicit GetConnectionOptionsClass(QStringList list, QObject *parent = nullptr);

signals:
    void signalSendConnOptions(QList<QStringList>);
    void signalAzsComplete();
    void signalFinished();
public slots:
    void slotGetConnOptions();
private:
    QStringList m_listTerm;
    QList<QStringList> m_listConnections;


};

#endif // GETCONNECTIONOPTIONSCLASS_H

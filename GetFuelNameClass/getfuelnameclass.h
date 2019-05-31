#ifndef GETFUELNAMECLASS_H
#define GETFUELNAMECLASS_H

#include "FuelNameWizard/statusthread.h"
#include "DataBases/databases.h"
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>


class GetFuelNameClass : public QObject
{
    Q_OBJECT
public:
    explicit GetFuelNameClass(QStringList connList, QObject *parent = nullptr);

signals:
    void finisList();
    void signalSendStatus(statusThread);

public slots:
    void getFuelList();
private:
    QStringList m_connList;
    statusThread currentStatus;
};

#endif // GETFUELNAMECLASS_H

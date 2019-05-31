#include "getfuelnameclass.h"
#include "LoggingCategories/loggingcategories.h"

enum statusList {
    CONNECT_TO_DATABASE,
    SELECT_FUEL_NAME,
    FINISHED
};


GetFuelNameClass::GetFuelNameClass(QStringList connList, QObject *parent) :
    QObject(parent),
    m_connList(connList)
{
    typedef statusThread st;
    qRegisterMetaType<st>("statusTh");

}

void GetFuelNameClass::getFuelList()
{
    currentStatus.terminalId=m_connList[0].toInt();
    currentStatus.currentStatus=CONNECT_TO_DATABASE;
    emit signalSendStatus(currentStatus);



//    QSqlQuery q;
//    q.prepare("select c.SERVER_NAME, c.DB_NAME, c.CON_PASSWORD from CONNECTIONS c "
//              "where c.TERMINAL_ID=:terminalID and c.CONNECT_ID=2");
//    q.bindValue(":terminalID", m_terminalID);
//    if(!q.exec()) qCritical(logCritical()) << "Не возможно получить данные о подключении АЗС" << q.lastError().text();
//    q.next();
//    qInfo(logInfo()) << q.value(0).toString();

    emit finisList();
}

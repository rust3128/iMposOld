#include "getfuelnameclass.h"
#include "LoggingCategories/loggingcategories.h"



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

    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE", m_connList[0]);

    db.setHostName(m_connList[1]);
    db.setDatabaseName(m_connList[2]);
    db.setUserName("SYSDBA");
    db.setPassword(m_connList[3]);

    if(!db.open()){
        qCritical(logCritical()) << Q_FUNC_INFO << "Не возможно подключится к базе данных АСЗ" << m_connList[0] << db.lastError().text();
        currentStatus.currentStatus=ERROR_OPEN_DATABASE;
        emit signalSendStatus(currentStatus);
        emit finisList();
        return;
    }
    currentStatus.currentStatus=SELECT_FUEL_NAME;
    emit signalSendStatus(currentStatus);

    QSqlQuery q = QSqlQuery(db);

    q.prepare("select t.TANK_ID, f.FUEL_ID, f.SHORTNAME, f.NAME from FUELS f "
              "LEFT JOIN tanks t ON t.FUEL_ID = f.FUEL_ID "
              "where f.ISACTIVE='T' "
              "order by t.TANK_ID");
    if(!q.exec()) {
        qCritical(logCritical()) << Q_FUNC_INFO << "Не возможно получить список видов топлива с АЗС." << m_connList[0] << q.lastError().text();
        currentStatus.currentStatus=ERROR_GET_FUEL_NAME;
        emit signalSendStatus(currentStatus);
        emit finisList();
        return;
    }
    AzsFuelName aFuelName;
    aFuelName.setTerminalID(m_connList[0].toInt());
    while(q.next()){
        aFuelName.insertFuelName(q.value(0).toInt(),q.value(1).toInt(),q.value(2).toString(),q.value(3).toString());
    }
    currentStatus.currentStatus=FINISHED;
    emit signalSendAzsFuelName(aFuelName);
    emit signalSendStatus(currentStatus);
    emit finisList();
}

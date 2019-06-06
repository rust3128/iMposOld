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

    emit finisList();
}

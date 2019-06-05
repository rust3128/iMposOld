#include "getconnectionoptionsclass.h"

GetConnectionOptionsClass::GetConnectionOptionsClass(QStringList list, QObject *parent)
    : QObject(parent), m_listTerm(list)
{

}

void GetConnectionOptionsClass::slotGetConnOptions()
{
    DataBases *db = new DataBases();
    if(!db->connectCentralDatabase()){
        qCritical(logCritical()) << Q_FUNC_INFO  << "Ошибка открытия баз данных.";
        emit signalFinished();
    }
    QSqlQuery q;
    static int colTerm = m_listTerm.size();
    for(int i=0;i<colTerm;++i){
            q.prepare("select c.TERMINAL_ID, c.SERVER_NAME, c.DB_NAME, c.CON_PASSWORD from CONNECTIONS c "
                      "where c.TERMINAL_ID=:terminalID and c.CONNECT_ID=2");
            q.bindValue(":terminalID", m_listTerm.at(i));
            if(!q.exec()) qCritical(logCritical()) << "Не возможно получить данные о подключении АЗС" << q.lastError().text();
            q.next();
            QStringList list;
            list << q.value(0).toString() << q.value(1).toString() << q.value(2).toString()  << passConv(q.value(3).toString());
            m_listConnections.append(list);
            emit signalAzsComplete();
    }
    emit signalSendConnOptions(m_listConnections);
    emit signalFinished();



}

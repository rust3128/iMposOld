#include "getfuelnameclass.h"
#include "LoggingCategories/loggingcategories.h"

GetFuelNameClass::GetFuelNameClass(QString terminal, QObject *parent) :
    QObject(parent),
    m_terminalID(terminal)
{

}

void GetFuelNameClass::getFuelList()
{
    qInfo(logInfo()) << "Thread for terminal" << m_terminalID;


    emit finisList();
}

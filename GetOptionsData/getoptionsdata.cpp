#include "getoptionsdata.h"
#include "LoggingCategories/loggingcategories.h"

GetOptionsData::GetOptionsData(QObject *parent) : QObject(parent)
{
    connectDatabase();
}

QVariant GetOptionsData::getOption(int optionID)
{
    QSqlQuery q = QSqlQuery(dbOptions);
    q.prepare("SELECT value FROM options WHERE option_id=:optionID");
    q.bindValue(":optionID",optionID);
    if(!q.exec()) {
        qCritical(logCritical()) << "Не удалось получить значение опции" << optionID << ".Причина" << q.lastError().text();
        return QVariant();
    }
    q.next();
    return q.value(0);

}

void GetOptionsData::connectDatabase()
{
    dbOptions = QSqlDatabase::database("options");

}

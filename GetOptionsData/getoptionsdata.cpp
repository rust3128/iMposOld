#include "getoptionsdata.h"
#include "LoggingCategories/loggingcategories.h"

GetOptionsData::GetOptionsData(QObject *parent) : QObject(parent)
{
    connectDatabase();
    getAllOptions();
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

void GetOptionsData::getAllOptions()
{
    QSqlQuery q = QSqlQuery(dbOptions);
    q.prepare("SELECT option_ID, value FROM options ORDER BY option_ID");
    if(!q.exec()) {
        qCritical(logCritical()) << "Не удалось получить значения опций. Причина" << q.lastError().text();
        return;
    }
    while (q.next()) {
        op.optionID = q.value(0).toInt();
        op.optionValue = q.value(1);
        m_listOptions.append(op);
    }

}
QList<option> GetOptionsData::sendAllOptions()
{
    return m_listOptions;
}

void GetOptionsData::saveChangedOptions(QList<option> op)
{
    QSqlQuery q = QSqlQuery(dbOptions);
    for (int i=0;i<op.size();++i) {
        q.prepare("UPDATE options SET value = :value WHERE option_ID = :optionID");
        q.bindValue(":optionID", op.at(i).optionID);
        q.bindValue(":value", op.at(i).optionValue);
        if(!q.exec()) {
            qCritical(logCritical()) << "Не удалось обновить опцию" << op.at(i).optionID << "Причина" << q.lastError().text();
        }
    }
}

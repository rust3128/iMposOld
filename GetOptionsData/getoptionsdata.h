#ifndef GETOPTIONSDATA_H
#define GETOPTIONSDATA_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

struct option
{
    int optionID;
    QVariant optionValue;
};

class GetOptionsData : public QObject
{
    Q_OBJECT
public:
    explicit GetOptionsData(QObject *parent = nullptr);
    QVariant getOption(int optionID);
    QList<option> sendAllOptions();
    void saveChangedOptions(QList<option> op);
signals:

public slots:
private:
    QSqlDatabase dbOptions;
    option op;
    QList<option> m_listOptions;
private:
    void connectDatabase();
    void getAllOptions();
};

#endif // GETOPTIONSDATA_H

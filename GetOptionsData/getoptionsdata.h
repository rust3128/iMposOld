#ifndef GETOPTIONSDATA_H
#define GETOPTIONSDATA_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

class GetOptionsData : public QObject
{
    Q_OBJECT
public:
    explicit GetOptionsData(QObject *parent = nullptr);
    QVariant getOption(int optionID);
signals:

public slots:
private:
    QSqlDatabase dbOptions;
private:
    void connectDatabase();
};

#endif // GETOPTIONSDATA_H

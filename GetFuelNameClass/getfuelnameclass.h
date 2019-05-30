#ifndef GETFUELNAMECLASS_H
#define GETFUELNAMECLASS_H

#include <QObject>

class GetFuelNameClass : public QObject
{
    Q_OBJECT
public:
    explicit GetFuelNameClass(QString terminal, QObject *parent = nullptr);

signals:
    void finisList();

public slots:
    void getFuelList();
private:
    QString m_terminalID;
};

#endif // GETFUELNAMECLASS_H

#ifndef STATUSTHREAD_H
#define STATUSTHREAD_H
#include <QObject>

struct statusThread
{
    int terminalId;
    int currentStatus;
};

enum statusList {
    CONNECT_TO_DATABASE,
    SELECT_FUEL_NAME,
    FINISHED
};


Q_DECLARE_METATYPE(statusThread);
#endif // STATUSTHREAD_H

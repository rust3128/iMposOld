#ifndef STATUSTHREAD_H
#define STATUSTHREAD_H
#include <QObject>

struct statusThread
{
    int terminalId;
    int currentStatus;
};

Q_DECLARE_METATYPE(statusThread);
#endif // STATUSTHREAD_H

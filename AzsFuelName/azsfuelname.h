#ifndef AZSFUELNAME_H
#define AZSFUELNAME_H

#include "FuelName/fuelname.h"
#include <QList>
#include <QString>

class AzsFuelName
{
public:
    AzsFuelName();


    int getTerminalID() const;
    void setTerminalID(int value);

    void insertFuelName(int tID, int fID, QString sN, QString n);

private:
    int terminalID;
    QList<FuelName> listFuel;
};

#endif // AZSFUELNAME_H

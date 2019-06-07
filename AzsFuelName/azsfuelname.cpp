#include "azsfuelname.h"

AzsFuelName::AzsFuelName()
{

}

int AzsFuelName::getTerminalID() const
{
    return terminalID;
}

void AzsFuelName::setTerminalID(int value)
{
    terminalID = value;
}

void AzsFuelName::insertFuelName(int tID, int fID, QString sN, QString n)
{
    FuelName fn;
    fn.setTankID(tID);
    fn.setFuelID(fID);
    fn.setShortName(sN);
    fn.setName(n);
    listFuel.append(fn);
}

QList<FuelName> AzsFuelName::getListFuel() const
{
    return listFuel;
}



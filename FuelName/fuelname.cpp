#include "fuelname.h"

FuelName::FuelName()
{

}

int FuelName::getTankID() const
{
    return tankID;
}

void FuelName::setTankID(int value)
{
    tankID = value;
}

int FuelName::getFuelID() const
{
    return fuelID;
}

void FuelName::setFuelID(int value)
{
    fuelID = value;
}

QString FuelName::getShortName() const
{
    return shortName;
}

void FuelName::setShortName(const QString &value)
{
    shortName = value;
}

QString FuelName::getName() const
{
    return name;
}

void FuelName::setName(const QString &value)
{
    name = value;
}

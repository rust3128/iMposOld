#ifndef FUELNAME_H
#define FUELNAME_H
#include <QString>

class FuelName
{
public:
    FuelName();

    int getTankID() const;
    void setTankID(int value);

    int getFuelID() const;
    void setFuelID(int value);

    QString getShortName() const;
    void setShortName(const QString &value);

    QString getName() const;
    void setName(const QString &value);

private:
    int tankID;
    int fuelID;
    QString shortName;
    QString name;
};

#endif // FUELNAME_H

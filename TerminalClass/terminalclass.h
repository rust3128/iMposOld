#ifndef TERMINALCLASS_H
#define TERMINALCLASS_H

#include <QString>

class TerminalClass
{
public:
    TerminalClass();
    int colParam() const;
    void setColParam(int colParam);

    int terminalID() const;
    void setTerminalID(int terminalID);

    QString terminalName() const;
    void setTerminalName(const QString &terminalName);

    int regionID() const;
    void setRegionID(int regionID);

    bool isCheced() const;
    void setIsCheced(bool isCheced);

private:
    int m_colParam;         // Количество членов классов
    bool m_isCheced;        // Признак выбора
    int m_terminalID;       // Номер терминала
    QString m_terminalName; // Наименование терминала
    int m_regionID;         // Код Региона

};

#endif // TERMINALCLASS_H

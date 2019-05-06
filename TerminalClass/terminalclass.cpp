#include "terminalclass.h"

#define COL_PARAMS 4

TerminalClass::TerminalClass()
{
    setColParam(COL_PARAMS);
}

int TerminalClass::colParam() const
{
    return m_colParam;
}

void TerminalClass::setColParam(int colParam)
{
    m_colParam = colParam;
}

int TerminalClass::terminalID() const
{
    return m_terminalID;
}

void TerminalClass::setTerminalID(int terminalID)
{
    m_terminalID = terminalID;
}

QString TerminalClass::terminalName() const
{
    return m_terminalName;
}

void TerminalClass::setTerminalName(const QString &terminalName)
{
    m_terminalName = terminalName;
}

int TerminalClass::regionID() const
{
    return m_regionID;
}

void TerminalClass::setRegionID(int regionID)
{
    m_regionID = regionID;
}

bool TerminalClass::isCheced() const
{
    return m_isCheced;
}

void TerminalClass::setIsCheced(bool isCheced)
{
    m_isCheced = isCheced;
}

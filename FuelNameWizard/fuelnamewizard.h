#ifndef FUELNAMEWIZARD_H
#define FUELNAMEWIZARD_H

#include "intropage.h"
#include "selectterminalpage.h"
#include "finalpage.h"
#include "showfuelnamepage.h"
#include <QWizard>

namespace Ui {
class FuelNameWizard;
}

class FuelNameWizard : public QWizard
{
    Q_OBJECT

public:
    explicit FuelNameWizard(QWidget *parent = nullptr);
    ~FuelNameWizard();

private:
    Ui::FuelNameWizard *ui;
    IntroPage *m_introPage;
    SelectTerminalPage *m_terminalPage;
    FinalPage *m_finalPage;
    ShowFuelNamePage *m_showFuelName;
private:
    void createWizardPage();
    void createConnections();
};

#endif // FUELNAMEWIZARD_H

#ifndef FUELNAMEWIZARD_H
#define FUELNAMEWIZARD_H

#include "intropage.h"
#include "selectterminalpage.h"

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
private:
    void createWizardPage();
};

#endif // FUELNAMEWIZARD_H

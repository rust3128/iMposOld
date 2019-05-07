#include "fuelnamewizard.h"
#include "ui_fuelnamewizard.h"
#include "pagelist.h"

FuelNameWizard::FuelNameWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::FuelNameWizard)
{
    ui->setupUi(this);

    createWizardPage();
}

FuelNameWizard::~FuelNameWizard()
{
    delete ui;
}

void FuelNameWizard::createWizardPage()
{
    m_introPage = new IntroPage();
    m_terminalPage = new SelectTerminalPage();
    m_finalPage = new FinalPage();
    m_showFuelName = new ShowFuelNamePage();

    this->setPage(INTRO_PAGE, m_introPage);
    this->setPage(SELECT_TERMINAL_PAGE, m_terminalPage);
    this->setPage(FINAL_PAGE, m_finalPage);
    this->setPage(SHOW_FUELNAME_PAGE, m_showFuelName);
    this->setStartId(INTRO_PAGE);
}

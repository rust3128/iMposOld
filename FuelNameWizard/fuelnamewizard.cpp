#include "fuelnamewizard.h"
#include "ui_fuelnamewizard.h"
#include "pagelist.h"
#include <QAbstractButton>

FuelNameWizard::FuelNameWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::FuelNameWizard)
{
    ui->setupUi(this);

    QList<QWizard::WizardButton> button_layout;
    button_layout << QWizard::Stretch <<
                     QWizard::NextButton <<
                     QWizard::FinishButton <<
                     QWizard::CancelButton;
    this->setButtonLayout(button_layout);

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
    m_setFuelName = new SetFuelNamePage();
    m_setAzsFuelName = new SetAzsFuelNamePage();

    createConnections();

    this->setPage(INTRO_PAGE, m_introPage);
    this->setPage(SELECT_TERMINAL_PAGE, m_terminalPage);
    this->setPage(FINAL_PAGE, m_finalPage);
    this->setPage(SHOW_FUELNAME_PAGE, m_showFuelName);
    this->setPage(CHANGE_FUELNAME_PAGE,m_setFuelName);
    this->setPage(SET_AZS_FUELNAME_PAGE, m_setAzsFuelName);
    this->setStartId(INTRO_PAGE);

}

void FuelNameWizard::createConnections()
{
    connect(m_terminalPage, &SelectTerminalPage::signalSendTermList,m_showFuelName,&ShowFuelNamePage::slotGetListTerm);
    connect(m_showFuelName, &ShowFuelNamePage::signalSendFuelNameList,m_finalPage,&FinalPage::slotGetListFuelName);
    connect(m_finalPage, &FinalPage::signalWizardFinished ,this,&FuelNameWizard::closeWizard );
}

void FuelNameWizard::closeWizard()
{
    this->accept();
}

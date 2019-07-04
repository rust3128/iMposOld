#include "setfuelnamepage.h"
#include "ui_setfuelnamepage.h"

SetFuelNamePage::SetFuelNamePage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SetFuelNamePage)
{
    ui->setupUi(this);

    createUI();
}

SetFuelNamePage::~SetFuelNamePage()
{
    delete ui;
}

void SetFuelNamePage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Выбор наименований топлива.</span></p></body></html>");
    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Выберите из предложенного списка наименования топлива которые необходимо установить на АЗС.</span></p></body></html>");
}


void SetFuelNamePage::initializePage()
{

}

bool SetFuelNamePage::validatePage()
{

}

bool SetFuelNamePage::isComplete() const
{

}

int SetFuelNamePage::nextId() const
{

}

#include "showfuelnamepage.h"
#include "ui_showfuelnamepage.h"

ShowFuelNamePage::ShowFuelNamePage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ShowFuelNamePage)
{
    ui->setupUi(this);
    createUI();
}

ShowFuelNamePage::~ShowFuelNamePage()
{
    delete ui;
}

void ShowFuelNamePage::createUI()
{
        this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Наименования топлива на АЗС.</span></p></body></html>");
}
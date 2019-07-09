#include "setazsfuelnamepage.h"
#include "ui_setazsfuelnamepage.h"

SetAzsFuelNamePage::SetAzsFuelNamePage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SetAzsFuelNamePage)
{
    ui->setupUi(this);
    createUI();
}

SetAzsFuelNamePage::~SetAzsFuelNamePage()
{
    delete ui;
}

void SetAzsFuelNamePage::createUI()
{
        this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Изменение наименовия топлива на АЗС.</span></p></body></html>");
}

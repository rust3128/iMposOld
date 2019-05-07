#include "finalpage.h"
#include "ui_finalpage.h"

FinalPage::FinalPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::FinalPage)
{
    ui->setupUi(this);

    this->setFinalPage(true);
    createUI();
}

FinalPage::~FinalPage()
{
    delete ui;
}

void FinalPage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Заключительный шаг.</span></p></body></html>");
//    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Выберите терминалы (АЗС) для который необходимо произвести с наименованиями видов топлива.</span></p></body></html>");

}

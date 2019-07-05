#include "setfuelnamepage.h"
#include "ui_setfuelnamepage.h"
#include "LoggingCategories/loggingcategories.h"

#include <QDate>


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
    ui->dateEdit->setDate(QDate::currentDate());
    ui->frame->hide();
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

void SetFuelNamePage::on_groupBoxDT_clicked()
{
    if(!ui->groupBoxDT->isChecked()){
        ui->checkBoxDTS->setChecked(false);
        ui->checkBoxDTW->setChecked(false);
    }
}

void SetFuelNamePage::on_groupBoxVIP_clicked()
{
    if(!ui->groupBoxVIP->isChecked()){
        ui->checkBoxVIPS->setChecked(false);
        ui->checkBoxVIPW->setChecked(false);
    }
}

void SetFuelNamePage::on_checkBoxDTS_clicked()
{
    ui->checkBoxDTW->setChecked(!ui->checkBoxDTS->isChecked());
}

void SetFuelNamePage::on_checkBoxDTW_clicked()
{
    ui->checkBoxDTS->setChecked(!ui->checkBoxDTW->isChecked());
}

void SetFuelNamePage::on_checkBoxVIPS_clicked()
{
    ui->checkBoxVIPW->setChecked(!ui->checkBoxVIPS->isChecked());
}

void SetFuelNamePage::on_checkBoxVIPW_clicked()
{
    ui->checkBoxVIPS->setChecked(!ui->checkBoxVIPW->isChecked());
}

void SetFuelNamePage::on_commandLinkButton_clicked()
{
    if(ui->frame->isHidden())
        return;
    ui->frame->show();
}

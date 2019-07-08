#include "setfuelnamepage.h"
#include "ui_setfuelnamepage.h"
#include "LoggingCategories/loggingcategories.h"
#include "SQLHighlighter/SQLHighlighter.h"
#include "pagelist.h"

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
    return ui->checkBox->isChecked();
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
    if(ui->frame->isVisible())
        return;
    if(ui->checkBoxDTS->isChecked() || ui->checkBoxDTW->isChecked() || ui->checkBoxVIPS->isChecked() || ui->checkBoxVIPW->isChecked())
        ui->frame->show();
    else
        return;
    listSQL.clear();
    QString dtName="";

    if(ui->checkBoxDTS->isChecked()) {
        dtName = ui->checkBoxDTS->text();
    } else {
        if(ui->checkBoxDTW->isChecked()){
            dtName=ui->checkBoxDTW->text();
        }
    }


//    dtName = (ui->checkBoxDTS->isChecked()) ? ui->checkBoxDTS->text() : "";
//    dtName = (ui->checkBoxDTW->isChecked()) ? ui->checkBoxDTW->text() : "";

    QString VPName="";

    if(ui->checkBoxVIPS->isChecked()) {
        VPName = ui->checkBoxVIPS->text();
    } else {
        if(ui->checkBoxVIPW->isChecked()){
            VPName=ui->checkBoxVIPW->text();
        }
    }


//    VPName = (ui->checkBoxVIPS->isChecked()) ? ui->checkBoxVIPS->text() : "";
//    VPName = (ui->checkBoxVIPW->isChecked()) ? ui->checkBoxVIPW->text() : "";


    QString infoMessage = ui->dateEdit->date().toString("dd.MM.yyyy");
    infoMessage += " будут устанвлены следующие наименования " + dtName + " " + VPName+".";
    ui->labelInfo->setText(infoMessage);

    if(dtName.size()>0)
        listSQL << "UPDATE FUELS SET NAME = '"+dtName+"' WHERE FUEL_ID = 7;";
    if(VPName.size()>0)
        listSQL << "UPDATE FUELS SET NAME = '"+VPName+"' WHERE FUEL_ID = 8;";
    listSQL << "UPDATE MIGRATEOPTIONS SET SVALUE = '"+ui->dateEdit->date().toString("yyyyMMdd")+"' WHERE MIGRATEOPTION_ID = 3400;";
    listSQL << "UPDATE MIGRATEOPTIONS SET SVALUE = '6' WHERE MIGRATEOPTION_ID = 3410;";
    listSQL << "commit;";

    new SQLHighlighter(ui->textEdit->document());

    ui->textEdit->append(listSQL.join("\n"));

}

void SetFuelNamePage::on_checkBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit this->completeChanged();
}

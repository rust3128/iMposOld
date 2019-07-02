#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "LoggingCategories/loggingcategories.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    options = new GetOptionsData();
    listOptions = options->sendAllOptions();
    m_isCritical = false;
    createConnections();
    createUI();

}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

bool OptionsDialog::getIsCritical()
{
    return m_isCritical;
}

void OptionsDialog::createUI()
{
    for (int i =0;i<listOptions.size();++i) {
        switch (listOptions.at(i).optionID) {
        case 1000:
            ui->checkBox1000->setChecked(listOptions.at(i).optionValue.toBool());
            break;
        case 1010:
            if(listOptions.at(i).optionValue.toBool()){
                ui->radioButtonRegion->setChecked(true);
                ui->radioButtonTerminal->setChecked(false);
            } else {
                ui->radioButtonRegion->setChecked(false);
                ui->radioButtonTerminal->setChecked(true);
            }
            break;
        default:
            break;
        }
    }
}

void OptionsDialog::createConnections()
{
    connect(ui->radioButtonRegion,&QRadioButton::clicked, this, &OptionsDialog::slotGroupBoxChanged);
    connect(ui->radioButtonTerminal,&QRadioButton::clicked, this, &OptionsDialog::slotGroupBoxChanged);
}

void OptionsDialog::on_buttonBox_accepted()
{
    opt.optionID=1010;
    if(ui->radioButtonRegion->isChecked())
        opt.optionValue = true;
    if(ui->radioButtonTerminal->isChecked())
        opt.optionValue = false;

    currentListOptions.append(opt);

    options->saveChangedOptions(currentListOptions);
    this->accept();
}

void OptionsDialog::on_buttonBox_rejected()
{
    this->reject();
}

void OptionsDialog::on_checkBox1000_clicked()
{
    m_isCritical = true;
    opt.optionID=1000;
    opt.optionValue = ui->checkBox1000->isChecked();
    currentListOptions.append(opt);
}



void OptionsDialog::slotGroupBoxChanged()
{


//    //(ui->radioButtonRegion->isChecked() ) ? opt.optionValue = true : opt.optionValue = false;

//    qInfo(logInfo()) << "OptionValue" <<  opt.optionValue.toBool();
//    qInfo(logInfo()) << "RadioRegions" << ui->radioButtonRegion->isChecked();
}

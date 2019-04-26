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
        default:
            break;
        }
    }
}

void OptionsDialog::on_buttonBox_accepted()
{
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

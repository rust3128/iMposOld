#include "intropage.h"
#include "ui_intropage.h"

IntroPage::IntroPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::IntroPage)
{
    ui->setupUi(this);
    createUI();

    this->registerField("checkView", ui->radioButtonView);
    this->registerField("checkEdit", ui->radioButtonEdit);
}

IntroPage::~IntroPage()
{
    delete ui;
}

void IntroPage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Шаг 1. Выбор действий.</span></p></body></html>");
    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Выберите действия которые необходимо произвести с наименованиями видов топлива на АЗС.</span></p></body></html>");
}


void IntroPage::initializePage()
{
    ui->radioButtonView->setChecked(false);
    ui->radioButtonEdit->setChecked(false);
}

bool IntroPage::isComplete() const
{
    if ( ui->radioButtonEdit->isChecked() || ui->radioButtonView->isChecked() )
        return true;
    else
        return false;
}



void IntroPage::on_radioButtonView_clicked()
{
    emit this->completeChanged();
}

void IntroPage::on_radioButtonEdit_clicked()
{
    emit this->completeChanged();
}

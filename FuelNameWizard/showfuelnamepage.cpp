#include "showfuelnamepage.h"
#include "ui_showfuelnamepage.h"
#include "LoggingCategories/loggingcategories.h"

#include <QTableWidgetItem>

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

void ShowFuelNamePage::slotGetListTerm(QStringList list)
{
    m_listTerm = list;
    qInfo(logInfo()) << m_listTerm;
}

void ShowFuelNamePage::createUI()
{
        this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Наименования топлива на АЗС.</span></p></body></html>");
}


void ShowFuelNamePage::initializePage()
{
    ui->tableWidget->setColumnCount(2);
    static int rowCount = m_listTerm.size();
    for(int i=0; i<rowCount; ++i){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(m_listTerm.at(i)));
    }

}

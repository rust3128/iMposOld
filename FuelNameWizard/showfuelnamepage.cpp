#include "showfuelnamepage.h"
#include "ui_showfuelnamepage.h"
#include "LoggingCategories/loggingcategories.h"
#include "ProgressBarDelegate/progressbardelegate.h"
#include "GetFuelNameClass/getfuelnameclass.h"

#include <QTableWidgetItem>
#include <QThread>

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
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    static int rowCount = m_listTerm.size();
    for(int i=0; i<rowCount; ++i){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(m_listTerm.at(i)));
        ui->tableWidget->setItem(i,1, new QTableWidgetItem("Ждем..."));
        ui->tableWidget->setItemDelegateForColumn(1, new ProgressBarDelegate);
        fuelNameList(m_listTerm.at(i));
    }
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

}

void ShowFuelNamePage::fuelNameList(QString terminal)
{
    GetFuelNameClass *getFuel = new GetFuelNameClass(terminal);
    QThread *thread = new QThread();

    getFuel->moveToThread(thread);

    connect(thread,&QThread::started, getFuel, &GetFuelNameClass::getFuelList);

    connect(thread, &QThread::started, this, &ShowFuelNamePage::slotStartGetFuel);

    connect(getFuel, &GetFuelNameClass::finisList, thread, &QThread::quit);
    connect(getFuel, &GetFuelNameClass::finisList, getFuel, &GetFuelNameClass::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();

}

void ShowFuelNamePage::slotStartGetFuel()
{

}


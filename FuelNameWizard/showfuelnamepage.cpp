#include "showfuelnamepage.h"
#include "passconv.h"
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

    statusList << "Подключение к базе данных АЗС..."
               << "Получение списка фидов топлива...."
               << "Готово.";
}

ShowFuelNamePage::~ShowFuelNamePage()
{
    delete ui;
}

void ShowFuelNamePage::slotGetListTerm(QStringList list)
{
    m_listTerm.clear();
    m_listTerm = list;
    qInfo(logInfo()) << m_listTerm;
}

void ShowFuelNamePage::getConnectionsInfo()
{
    static int colTerm = m_listTerm.size();
    QSqlQuery q;
    for(int i=0;i<colTerm;++i){
            q.prepare("select c.TERMINAL_ID, c.SERVER_NAME, c.DB_NAME, c.CON_PASSWORD from CONNECTIONS c "
                      "where c.TERMINAL_ID=:terminalID and c.CONNECT_ID=2");
            q.bindValue(":terminalID", m_listTerm.at(i));
            if(!q.exec()) qCritical(logCritical()) << "Не возможно получить данные о подключении АЗС" << q.lastError().text();
            q.next();
            QStringList list;
            list << q.value(0).toString() << q.value(1).toString() << q.value(2).toString()  << passConv(q.value(3).toString());
            listConnections.append(list);

    }
//    qInfo(logInfo()) << listConnections;
}


void ShowFuelNamePage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Наименования топлива на АЗС.</span></p></body></html>");
    ui->groupBoxGetFuelName->hide();

}



void ShowFuelNamePage::initializePage()
{
    QApplication::processEvents();
//    ui->tableWidget->setColumnCount(2);
//    ui->tableWidget->horizontalHeader()->hide();
//    ui->tableWidget->verticalHeader()->hide();
//    getConnectionsInfo();
//    static int rowCount = m_listTerm.size();
//    for(int i=0; i<rowCount; ++i){
//        ui->tableWidget->insertRow(i);
//        ui->tableWidget->setItem(i,0, new QTableWidgetItem(m_listTerm.at(i)));
//        ui->tableWidget->setItem(i,1, new QTableWidgetItem("Ждем..."));
////        ui->tableWidget->setItemDelegateForColumn(1, new ProgressBarDelegate);
//        fuelNameList(listConnections.at(i));
//    }
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    static int colTerm = m_listTerm.size();
    ui->progressBar->setRange(0,colTerm);
    ui->progressBar->setFormat("Получено %v из %m");
    int progress = 0;
    QSqlQuery q;
    for(int i=0;i<colTerm;++i){
            q.prepare("select c.TERMINAL_ID, c.SERVER_NAME, c.DB_NAME, c.CON_PASSWORD from CONNECTIONS c "
                      "where c.TERMINAL_ID=:terminalID and c.CONNECT_ID=2");
            q.bindValue(":terminalID", m_listTerm.at(i));
            if(!q.exec()) qCritical(logCritical()) << "Не возможно получить данные о подключении АЗС" << q.lastError().text();
            q.next();
            QStringList list;
            list << q.value(0).toString() << q.value(1).toString() << q.value(2).toString()  << passConv(q.value(3).toString());
            listConnections.append(list);
            QApplication::processEvents();
            ++progress;
            ui->progressBar->setValue(progress);
    }


}

void ShowFuelNamePage::fuelNameList(QStringList connList)
{
    GetFuelNameClass *getFuel = new GetFuelNameClass(connList);
    QThread *thread = new QThread();

    getFuel->moveToThread(thread);

    connect(thread,&QThread::started, getFuel, &GetFuelNameClass::getFuelList);

    connect(getFuel,&GetFuelNameClass::signalSendStatus,this,&ShowFuelNamePage::slotGetStatusThread);

    connect(getFuel, &GetFuelNameClass::finisList, thread, &QThread::quit);
    connect(getFuel, &GetFuelNameClass::finisList, getFuel, &GetFuelNameClass::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();

}



void ShowFuelNamePage::slotGetStatusThread(statusThread stTh)
{
    qInfo(logInfo()) << "hello from thread" << stTh.terminalId << statusList[stTh.currentStatus];
}





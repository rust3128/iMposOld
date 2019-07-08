#include "showfuelnamepage.h"
#include "passconv.h"
#include "ui_showfuelnamepage.h"
#include "pagelist.h"
#include "LoggingCategories/loggingcategories.h"
#include "ProgressBarDelegate/progressbardelegate.h"
#include "GetFuelNameClass/getfuelnameclass.h"

#include <QTableWidgetItem>
#include <QThread>
#include <QIcon>

ShowFuelNamePage::ShowFuelNamePage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ShowFuelNamePage)
{
    ui->setupUi(this);
    createUI();

    statusList << "Подключение к базе данных АЗС..."
               << "Получение списка видов топлива...."
               << "Готово."
               << "Ошибка открытия базы данных АЗС!"
               << "Ошибка получения списка наименований топлива";

    m_listTerm.clear();

    colConnect=colSelect=colErrorTodatabase=colErrogSelect=colFinishet=0;

    connect(this,&ShowFuelNamePage::signalGoFuelName,this,&ShowFuelNamePage::fuelNameList);
}

ShowFuelNamePage::~ShowFuelNamePage()
{
    delete ui;
}


void ShowFuelNamePage::slotGetListTerm(QStringList list)
{
    m_listTerm.clear();
    m_listTerm = list;
}



void ShowFuelNamePage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Наименования топлива на АЗС.</span></p></body></html>");
    ui->groupBoxGetFuelName->hide();


    ui->tableWidget->setColumnCount(2);
    //ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "АЗС" << "Статус");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

}

void ShowFuelNamePage::initializePage()
{
        isWorkComplete=false;
        //Создаем объект класса и передаем ему параметры
        GetConnectionOptionsClass *lsConnnecions = new GetConnectionOptionsClass(m_listTerm);



        //Создаем поток в которм будут производиться наша выборка
        QThread *thread = new QThread();
        //Перемещаем объект класса в поток
        lsConnnecions->moveToThread(thread);

        ////Сигналы и слоты для взаимидействия с потоком

        //при старте потока выполняем некоторые действия в текущем потоке.
        //В моем случае на просто засекаю начало выбоки данных
        connect(thread,&QThread::started,this,&ShowFuelNamePage::slotStartConnectionsList);
        //При старте потока начинаем выборку данных
        connect(thread,&QThread::started,lsConnnecions,&GetConnectionOptionsClass::slotGetConnOptions);

        connect(lsConnnecions,&GetConnectionOptionsClass::signalAzsComplete,this,&ShowFuelNamePage::slotAzsComplete);
colConnect=colSelect=colErrorTodatabase=colErrogSelect=colFinishet=0;
        connect(lsConnnecions,&GetConnectionOptionsClass::signalSendConnOptions,this,&ShowFuelNamePage::slotGetConnectionsList,Qt::DirectConnection);


        //Окончание работы потока по завершению выбрки данных
        connect(lsConnnecions,&GetConnectionOptionsClass::signalFinished,thread,&QThread::quit);
        //Удаляем объект в потоке
        connect(lsConnnecions,&GetConnectionOptionsClass::signalFinished,lsConnnecions,&GetConnectionOptionsClass::deleteLater);
        //Вы полняем действия по в основном потоке после завершения дочернего
        connect(lsConnnecions,&GetConnectionOptionsClass::signalFinished,this,&ShowFuelNamePage::slotFinishConnectionsList);
        //Прощаемся с дочерним потоком
        connect(thread,&QThread::finished,thread,&QThread::deleteLater);

        //Запускаем поток
        thread->start();
}


void ShowFuelNamePage::slotStartConnectionsList()
{
    ui->progressBar->setRange(0,m_listTerm.size());
    ui->progressBar->setFormat("Обработано %v из %m");
    ui->progressBar->setValue(0);
}

void ShowFuelNamePage::slotAzsComplete()
{
    ui->progressBar->setValue(ui->progressBar->value()+1);
}



void ShowFuelNamePage::slotGetConnectionsList(QList<QStringList> list)
{
    listConnections.clear();
    listConnections = list;


}

void ShowFuelNamePage::slotFinishConnectionsList()
{
    ui->groupBoxGetFuelName->show();
    ui->groupBoxProgress->hide();

    emit signalGoFuelName();
}


void ShowFuelNamePage::fuelNameList()
{

    int rowCount =listConnections.size();
    int colThread = 0;
    for(int i=0; i<rowCount; ++i){
        GetFuelNameClass *getFuel = new GetFuelNameClass(listConnections.at(i));
        QThread *thread = new QThread();

        getFuel->moveToThread(thread);


        connect(thread,&QThread::started,this,&ShowFuelNamePage::slotStartGetFuelName);
        connect(thread,&QThread::started, getFuel, &GetFuelNameClass::getFuelList);

        connect(getFuel,&GetFuelNameClass::signalSendStatus,this,&ShowFuelNamePage::slotGetStatusThread,Qt::UniqueConnection);

        connect(getFuel,&GetFuelNameClass::signalSendAzsFuelName,this,&ShowFuelNamePage::slotGetAzsFuelName,Qt::DirectConnection);

        connect(getFuel, &GetFuelNameClass::finisList, getFuel, &GetFuelNameClass::deleteLater);
        connect(getFuel, &GetFuelNameClass::finisList, thread, &QThread::quit);

        connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        thread->start();
        colThread++;
    }
    qInfo(logInfo()) << "Count connections = " << rowCount << "Count Thread" << colThread;

}

void ShowFuelNamePage::slotStartGetFuelName()
{
    ui->progressBarFuel->setRange(0, m_listTerm.size());
    ui->progressBarFuel->setValue(0);
}


void ShowFuelNamePage::slotGetAzsFuelName(AzsFuelName aFN)
{

//    qInfo(logInfo()) << "Terminal ID" << aFN.getTerminalID();
//    qInfo(logInfo()) << aFN.getListFuel().at(0).getName() ;
    listFuelName.append(aFN);
}


void ShowFuelNamePage::slotGetStatusThread(statusThread status)
{
//    qInfo(logInfo()) << "hello from thread" << stTh.terminalId << statusList[stTh.currentStatus];
    stTh=status;
//    int colConnect,colSelect,colErrorTodatabase,colErrogSelect,colFinishet;
//    colConnect=colSelect=colErrorTodatabase=colErrogSelect=colFinishet=0;

    switch (stTh.currentStatus) {
    case CONNECT_TO_DATABASE:
        statusConnectToDatabase();
        colConnect++;
        break;
    case SELECT_FUEL_NAME:
        statusSelectFuelName();
        colSelect++;
        break;
    case ERROR_OPEN_DATABASE:
        statusErrorConnectDatabase();
        ui->progressBarFuel->setValue(ui->progressBarFuel->value()+1);
        colErrorTodatabase++;
        break;
    case ERROR_GET_FUEL_NAME:
        statusSelectFuelName();
        ui->progressBarFuel->setValue(ui->progressBarFuel->value()+1);
        colErrogSelect++;
        break;
    case FINISHED:
        statusFinished();
        ui->progressBarFuel->setValue(ui->progressBarFuel->value()+1);
        colFinishet++;
        break;
    default:
        break;
    }

//    if(ui->progressBarFuel->value() == ui->progressBarFuel->maximum()){
//        isWorkComplete = true;
//        emit completeChanged();
//    }

        if(colConnect == (colSelect+colErrorTodatabase+colErrogSelect)){
            isWorkComplete = true;
            emit completeChanged();
        }

//    ui->label->setText("Обработано: "+QString::number(ui->progressBarFuel->value())+
//                       " из "+QString::number(ui->progressBarFuel->maximum()));
    ui->label->setText("Всего: "+QString::number(ui->progressBarFuel->maximum())
                       +". Обработано: "+QString::number(colSelect)
                       +". Ошибок: "+QString::number(colErrogSelect+colErrorTodatabase) );

//    qInfo(logInfo()) << "COL CONNECT" << colConnect << "Col Select" << colSelect << "colErrorTodatabase" << colErrorTodatabase
//                     << "colErrogSelect" << colErrogSelect << "colFinishet" << colFinishet;
}



void ShowFuelNamePage::statusConnectToDatabase()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row,0, new QTableWidgetItem(QString::number(stTh.terminalId)));
    ui->tableWidget->setItem(row,1, new QTableWidgetItem(statusList[stTh.currentStatus]));
    ui->tableWidget->item(row,0)->setIcon(QIcon(":/Picts/GasStation.png"));
    ui->tableWidget->item(row,1)->setIcon(QIcon(":/Picts/database.png"));
    ui->tableWidget->item(row,1)->setBackgroundColor("#F4FA58");
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(36);
}

void ShowFuelNamePage::statusSelectFuelName()
{
    int rowCount = ui->tableWidget->rowCount();
    for(int i = 0; i<rowCount; ++i) {
        if(ui->tableWidget->item(i,0)->text().toInt() == stTh.terminalId) {
            ui->tableWidget->item(i,1)->setText(statusList[stTh.currentStatus]);
            ui->tableWidget->item(i,1)->setBackgroundColor("#D7DF01");
            ui->tableWidget->item(i,1)->setIcon(QIcon(":/Picts/selectfuel.png"));
            break;
        }
    }
}

void ShowFuelNamePage::statusErrorGetFuelName()
{
    int rowCount = ui->tableWidget->rowCount();
    for(int i = 0; i<rowCount; ++i) {
        if(ui->tableWidget->item(i,0)->text().toInt() == stTh.terminalId) {
            ui->tableWidget->item(i,1)->setText(statusList[stTh.currentStatus]);
            ui->tableWidget->item(i,1)->setBackgroundColor("#DF01A5");
            ui->tableWidget->item(i,1)->setIcon(QIcon(":/Picts/error.png"));
            break;
        }
    }
}

void ShowFuelNamePage::statusErrorConnectDatabase()
{
    int rowCount = ui->tableWidget->rowCount();
    for(int i = 0; i<rowCount; ++i) {
        if(ui->tableWidget->item(i,0)->text().toInt() == stTh.terminalId) {
            ui->tableWidget->item(i,1)->setText(statusList[stTh.currentStatus]);
            ui->tableWidget->item(i,1)->setBackgroundColor("#FE2E2E");
            ui->tableWidget->item(i,1)->setIcon(QIcon(":/Picts/error.png"));
            break;
        }
    }
}

void ShowFuelNamePage::statusFinished()
{
    int rowCount = ui->tableWidget->rowCount();
    for(int i = 0; i<rowCount; ++i) {
        if(ui->tableWidget->item(i,0)->text().toInt() == stTh.terminalId) {
            ui->tableWidget->item(i,1)->setText(statusList[stTh.currentStatus]);
            ui->tableWidget->item(i,1)->setBackgroundColor("#BFFF00");
            ui->tableWidget->item(i,1)->setIcon(QIcon(":/Picts/Accept.png"));

            break;
        }
    }
}



bool ShowFuelNamePage::validatePage()
{

    if(listFuelName.size()>0){
        emit signalSendFuelNameList(listFuelName);
        return true;
    } else {
        return false;
    }
}


bool ShowFuelNamePage::isComplete() const
{
//    qInfo(logInfo()) << Q_FUNC_INFO << listFuelName.size();
//    if(listFuelName.size() == m_listTerm.size()) {
//        return true;
//    } else {
//        return false;
//    }
    return isWorkComplete;
//    return true;
}


int ShowFuelNamePage::nextId() const
{
    return FINAL_PAGE;
}

#include "fuelnamedialog.h"
#include "ui_fuelnamedialog.h"

FuelNameDialog::FuelNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuelNameDialog)
{
    ui->setupUi(this);

    createListTerminals();
    createModelterminals();
}

FuelNameDialog::~FuelNameDialog()
{
    delete ui;
}

void FuelNameDialog::createModelterminals()
{
    qInfo(logInfo()) << "Заружено терминалов:" << listTerminals.size();
    CheckBoxDelegate *delegate = new CheckBoxDelegate();
    modelTerminals = new ModelTerminals(listTerminals);


    ui->tableViewTerminals->setModel(modelTerminals);
    ui->tableViewTerminals->setItemDelegateForColumn(0,delegate);

    ui->tableViewTerminals->verticalHeader()->hide();
    ui->tableViewTerminals->resizeColumnsToContents();

    for(int i=0; i<10; ++i){

        qInfo(logInfo()) << modelTerminals->data(modelTerminals->index(i, 0,QModelIndex()),Qt::DisplayRole) << modelTerminals->data(modelTerminals->index(i, 1,QModelIndex()),Qt::DisplayRole);

    }

}

void FuelNameDialog::createListTerminals()
{
    QSqlQuery q;
    TerminalClass t;
    if(!q.exec("SELECT t.TERMINAL_ID, TRIM(t.name) AS NAME, t.OWNER_ID AS REGION, c.SERVER_NAME  FROM TERMINALS t "
               "LEFT JOIN CONNECTIONS c ON c.TERMINAL_ID = t.TERMINAL_ID "
               "WHERE t.TERMINALTYPE = 3 AND c.CONNECT_ID = 2 "
               "ORDER BY t.TERMINAL_ID")) {
        qInfo(logInfo()) << Q_FUNC_INFO  << "Не возможно получить список терминалов" << q.lastError().text();
        return;
    }
    while(q.next()){
        t.setIsCheced(false);
        t.setTerminalID(q.value(0).toInt());
        t.setTerminalName(q.value(1).toString());
        t.setRegionID(q.value(2).toInt());
        t.setServerName(q.value(3).toString());
        listTerminals.append(t);
    }

}

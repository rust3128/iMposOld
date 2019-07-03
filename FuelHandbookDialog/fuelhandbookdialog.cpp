#include "fuelhandbookdialog.h"
#include "ui_fuelhandbookdialog.h"
#include "AddFuelNameDialog/addfuelnamedialog.h"

FuelHandbookDialog::FuelHandbookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuelHandbookDialog)
{
    ui->setupUi(this);
    createModel();
    createUI();

}

FuelHandbookDialog::~FuelHandbookDialog()
{
    delete ui;
}


void FuelHandbookDialog::createUI()
{
    ui->tableView->setModel(modelName);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

}

void FuelHandbookDialog::createModel()
{
    QSqlDatabase db = QSqlDatabase::database("options");

    modelName = new QSqlTableModel(this,db);

    modelName->setTable("fuelnames");
    modelName->setFilter("1=1 order by fuel_id");
    modelName->select();
    modelName->setHeaderData(2,Qt::Horizontal,"Наименование топлива\nв кассе");
    modelName->setHeaderData(1,Qt::Horizontal,"Код\nв базе");
    modelName->setHeaderData(3,Qt::Horizontal,"Коменнатрии");

}

void FuelHandbookDialog::slotUpdateModels()
{
    modelName->select();
}

void FuelHandbookDialog::on_pushButtonAdd_clicked()
{
    AddFuelNameDialog *addFuelDlg = new AddFuelNameDialog(-1);
    connect(addFuelDlg, &AddFuelNameDialog::signalReady, this, &FuelHandbookDialog::slotUpdateModels);

    addFuelDlg->setWindowTitle("Добавить наименование");
    addFuelDlg->exec();
}



void FuelHandbookDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    AddFuelNameDialog *addFuelDlg = new AddFuelNameDialog(index.row());
    connect(addFuelDlg, &AddFuelNameDialog::signalReady, this, &FuelHandbookDialog::slotUpdateModels);

    addFuelDlg->setWindowTitle("Изменить наименование");
    addFuelDlg->exec();
}

void FuelHandbookDialog::on_pushButtonClose_clicked()
{
    this->reject();
}

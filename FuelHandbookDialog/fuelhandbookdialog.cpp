#include "fuelhandbookdialog.h"
#include "ui_fuelhandbookdialog.h"

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
    modelName->select();
    modelName->setHeaderData(1,Qt::Horizontal,"Наименование топлива");
    modelName->setHeaderData(2,Qt::Horizontal,"Коменнатрии");
}

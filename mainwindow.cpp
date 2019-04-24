#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FuelNameDialog/fuelnamedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFuelName_triggered()
{
    FuelNameDialog *dlgFuelName = new FuelNameDialog();
    this->setCentralWidget(dlgFuelName);
    dlgFuelName->exec();
}

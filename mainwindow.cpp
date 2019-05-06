#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "FuelNameWizard/fuelnamewizard.h"
#include "OptionsDialog/optionsdialog.h"
#include <QMessageBox>

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
    FuelNameWizard *dlgFuelName = new FuelNameWizard();
    this->setCentralWidget(dlgFuelName);
    dlgFuelName->exec();
}

void MainWindow::on_actionOptions_triggered()
{
    OptionsDialog *dlgOptions = new OptionsDialog();
    dlgOptions->move(this->geometry().center().x() - dlgOptions->geometry().center().x(),
                     this->geometry().center().y() - dlgOptions->geometry().center().y());
    dlgOptions->exec();
    if(dlgOptions->result() == QDialog::Accepted && dlgOptions->getIsCritical() ) {

        QMessageBox::critical(this,"Внимание",
                              "Изменены критические настройки системы!\nНеобходимо перезапуск программы.");
        this->close();
    }

}

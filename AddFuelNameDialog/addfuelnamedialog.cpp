#include "addfuelnamedialog.h"
#include "ui_addfuelnamedialog.h"
#include <QPushButton>

AddFuelNameDialog::AddFuelNameDialog(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFuelNameDialog)
{
    ui->setupUi(this);

    setupModel();


    if(row == -1){
        model->insertRow(model->rowCount(QModelIndex()));
        mapper->toLast();
    } else {
        mapper->setCurrentModelIndex(model->index(row,0));
    }

    createUI();


}

AddFuelNameDialog::~AddFuelNameDialog()
{
    delete ui;
}

void AddFuelNameDialog::setupModel()
{
    QSqlDatabase db = QSqlDatabase::database("options");

    model = new QSqlTableModel(this,db);
    model->setTable("fuelnames");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);

    mapper->addMapping(ui->spinBox,1);
    mapper->addMapping(ui->lineEditFuelName,2);
    mapper->addMapping(ui->plainTextEditComments,3);

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);


}

void AddFuelNameDialog::createUI()
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
}

void AddFuelNameDialog::on_lineEditFuelName_textChanged(const QString &arg1)
{
    if(arg1.size()>0)
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    else
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
}

void AddFuelNameDialog::on_buttonBox_accepted()
{
    mapper->submit();
    model->submitAll();
    emit signalReady();
    this->close();
}

#include "setfuelnamepage.h"
#include "ui_setfuelnamepage.h"


SetFuelNamePage::SetFuelNamePage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SetFuelNamePage)
{
    ui->setupUi(this);
    createModels();
    createUI();
}

SetFuelNamePage::~SetFuelNamePage()
{
    delete ui;
}



void SetFuelNamePage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Выбор наименований топлива.</span></p></body></html>");
    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Выберите из предложенного списка наименования топлива которые необходимо установить на АЗС.</span></p></body></html>");

    const int rowCount = modelFuel->rowCount();
//    QStringList _fuelList;
    for(int i = 0; i<rowCount; ++i) {
        QListWidgetItem *item = new QListWidgetItem(modelFuel->data(modelFuel->index(i,2,QModelIndex()),Qt::DisplayRole).toString());
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(item);
        highlightChecked(item);
    }

    connect(ui->listWidget,&QListWidget::itemChanged,this, &SetFuelNamePage::highlightChecked);

}

void SetFuelNamePage::highlightChecked(QListWidgetItem *item)
{
    this->completeChanged();
    if(item->checkState() == Qt::Checked)
        item->setBackground(QColor("#ffffb2"));
    else
        item->setBackground(QColor("#ffffff"));
}

void SetFuelNamePage::createModels()
{
    QSqlDatabase db = QSqlDatabase::database("options");

    modelFuel = new QSqlTableModel(this, db);
    modelFuel->setTable("fuelnames");
    modelFuel->setFilter("1=1 order by fuel_id");
    modelFuel->select();
}


void SetFuelNamePage::initializePage()
{

}

bool SetFuelNamePage::validatePage()
{

}

bool SetFuelNamePage::isComplete() const
{

}

int SetFuelNamePage::nextId() const
{

}

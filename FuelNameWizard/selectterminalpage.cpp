#include "selectterminalpage.h"
#include "ui_selectterminalpage.h"
#include "pagelist.h"



SelectTerminalPage::SelectTerminalPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SelectTerminalPage)
{
    ui->setupUi(this);

    createUI();
}

SelectTerminalPage::~SelectTerminalPage()
{
    delete ui;
}

void SelectTerminalPage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Шаг 2. Выбор терминалов.</span></p></body></html>");
    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Выберите терминалы (АЗС) для который необходимо произвести с наименованиями видов топлива.</span></p></body></html>");

    ui->toolButtonAddTerm->setEnabled(false);
}

void SelectTerminalPage::createModelTerminals()
{
    qInfo(logInfo()) << "Заружено терминалов:" << m_listTerminals.size();
    CheckBoxDelegate *delegate = new CheckBoxDelegate();
    m_modelTerminals = new ModelTerminals(m_listTerminals);

    m_proxyModel = new QSortFilterProxyModel();
    m_proxyModel->setSourceModel(m_modelTerminals);

    ui->tableViewTerminals->setModel(m_proxyModel);
    ui->tableViewTerminals->setItemDelegateForColumn(0,delegate);

    ui->tableViewTerminals->verticalHeader()->hide();
    ui->tableViewTerminals->hideColumn(3);
    ui->tableViewTerminals->verticalHeader()->setDefaultSectionSize(ui->tableViewTerminals->verticalHeader()->minimumSectionSize());
    ui->tableViewTerminals->resizeColumnsToContents();

}

void SelectTerminalPage::createListTerminals()
{
    QSqlQuery q;
    TerminalClass t;
    if(!q.exec("SELECT t.TERMINAL_ID, TRIM(t.NAME), t.OWNER_ID from terminals t "
               "WHERE t.TERMINALTYPE=3 "
               "ORDER BY t.TERMINAL_ID")) {
        qInfo(logInfo()) << Q_FUNC_INFO  << "Не возможно получить список терминалов" << q.lastError().text();
        return;
    }
    while(q.next()){
        t.setIsCheced(false);
        t.setTerminalID(q.value(0).toInt());
        t.setTerminalName(q.value(1).toString());
        t.setRegionID(q.value(2).toInt());

        m_listTerminals.append(t);
    }
}




void SelectTerminalPage::initializePage()
{
    createListTerminals();
    createModelTerminals();

    connect(ui->tableViewTerminals->model(),&QAbstractTableModel::dataChanged,this,&SelectTerminalPage::terminalChecked);
}

bool SelectTerminalPage::validatePage()
{
    qInfo(logInfo()) << "Helow from" << Q_FUNC_INFO;
    const int rowCount = ui->listWidget->count();
    QListWidgetItem *item = nullptr;
    m_terminalsGo.clear();
    for(int i=0; i<rowCount; ++i){
        item = ui->listWidget->item(i);
        if(item->checkState() == Qt::Checked)
            m_terminalsGo.append(item->text());
    }
    return (m_terminalsGo.size()>0) ? true : false;

}

bool SelectTerminalPage::isComplete() const
{
    const int rowCount = ui->listWidget->count();
    QListWidgetItem *item = nullptr;
    unsigned int selTerm = 0;
    for(int i=0; i<rowCount; ++i){
        item = ui->listWidget->item(i);
        if(item->checkState() == Qt::Checked)
            ++selTerm;
    }
    return (selTerm>0) ? true : false;

}

int SelectTerminalPage::nextId() const
{
    int nextPage = 0;
    if(field("checkView").toBool())
        nextPage = SHOW_FUELNAME_PAGE;
    if(field("checkEdit").toBool())
        nextPage = FINAL_PAGE;
    return nextPage;
}

void SelectTerminalPage::terminalChecked()
{
    const int rowCount = ui->tableViewTerminals->model()->rowCount(QModelIndex());
    unsigned int colChecked = 0;
    for(int i =0; i < rowCount; ++i){
        if(ui->tableViewTerminals->model()->index(i,0).data(Qt::CheckStateRole).toInt() == Qt::Checked){
            ++colChecked;
        }
    }
    ui->toolButtonAddTerm->setEnabled(colChecked>0);
}



void SelectTerminalPage::on_toolButtonAddTerm_clicked()
{
    const int rowCount = ui->tableViewTerminals->model()->rowCount(QModelIndex());
    m_listSelectetTerminals.clear();
    ui->listWidget->clear();
    for(int i =0; i < rowCount; ++i){
        if(ui->tableViewTerminals->model()->index(i,0).data(Qt::CheckStateRole).toInt() == Qt::Checked){
            m_listSelectetTerminals.append(ui->tableViewTerminals->model()->index(i,1).data(Qt::DisplayRole).toString());
        }
    }
    ui->listWidget->addItems(m_listSelectetTerminals);
    const int rowSelected = ui->listWidget->count();
    QListWidgetItem *item = nullptr;
    for(int i=0; i< rowSelected; ++i ) {
        item = ui->listWidget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        highlightChecked(item);
    }

    connect(ui->listWidget,&QListWidget::itemChanged,this, &SelectTerminalPage::highlightChecked);

}

void SelectTerminalPage::highlightChecked(QListWidgetItem *item)
{
    this->completeChanged();
    if(item->checkState() == Qt::Checked)
        item->setBackgroundColor(QColor("#ffffb2"));
    else
        item->setBackgroundColor(QColor("#ffffff"));
}



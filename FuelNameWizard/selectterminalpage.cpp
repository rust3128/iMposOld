#include "selectterminalpage.h"
#include "ui_selectterminalpage.h"
#include "pagelist.h"
#include "GetOptionsData/getoptionsdata.h"




SelectTerminalPage::SelectTerminalPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SelectTerminalPage)
{
    ui->setupUi(this);

    createUI();
    m_terminalsGo.clear();
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
    if(!q.exec("SELECT DISTINCT t.TERMINAL_ID, TRIM(t.NAME), t.OWNER_ID from terminals t "
               "LEFT JOIN shifts s ON s.TERMINAL_ID = t.TERMINAL_ID "
               "WHERE t.TERMINALTYPE=3 and s.SHIFT_ID >1"
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

void SelectTerminalPage::createModelRegions()
{
    m_modelRegions = new QSqlQueryModel(this);

    GetOptionsData opt;
    if(opt.getOption(1010).toBool()){
        m_modelRegions->setQuery("select t.region_id, trim(t.NAME) from TERMINALS t "
                                 "where t.TERMINALTYPE=2 "
                                 "order by t.TERMINAL_ID ");
    } else {
        m_modelRegions->setQuery("select t.terminal_id, trim(t.NAME) from TERMINALS t "
                                 "where t.TERMINALTYPE=2 "
                                 "order by t.TERMINAL_ID ");
    }


    ui->comboBoxRegions->setModel(m_modelRegions);
    ui->comboBoxRegions->setModelColumn(1);
    ui->comboBoxRegions->setCurrentIndex(-1);

}




void SelectTerminalPage::initializePage()
{
    createListTerminals();
    createModelTerminals();
    createModelRegions();

    connect(ui->tableViewTerminals->model(),&QAbstractTableModel::dataChanged,this,&SelectTerminalPage::terminalChecked);
}

bool SelectTerminalPage::validatePage()
{

    int rowCount = ui->listWidget->count();
    QListWidgetItem *item = nullptr;
    m_terminalsGo.clear();
    for(int i=0; i<rowCount; ++i){
        item = ui->listWidget->item(i);
        if(item->checkState() == Qt::Checked)
            m_terminalsGo.append(item->text());
    }

    if(m_terminalsGo.size()>0){
        emit signalSendTermList(m_terminalsGo);
        return true;
    } else {
        return false;
    }

}

bool SelectTerminalPage::isComplete() const
{
    int rowCount = ui->listWidget->count();
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
    int rowCount = ui->tableViewTerminals->model()->rowCount(QModelIndex());
    unsigned int colChecked = 0;
    for(int i =0; i < rowCount; ++i){
        if(ui->tableViewTerminals->model()->index(i,0).data(Qt::CheckStateRole).toInt() == Qt::Checked){
            ++colChecked;
        }
    }
    ui->toolButtonAddTerm->setEnabled(colChecked>0);
    m_proxyModel->sort(0,Qt::DescendingOrder);
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
        item->setBackground(QColor("#ffffb2"));
    else
        item->setBackground(QColor("#ffffff"));
}



void SelectTerminalPage::on_toolButtonSelectAllTerminals_clicked()
{
    static int rowCount = m_modelTerminals->rowCount(QModelIndex());
    for(int i=0; i<rowCount; ++i){
        m_modelTerminals->setData(m_modelTerminals->index(i,0),Qt::Checked, Qt::CheckStateRole);
    }
}

void SelectTerminalPage::on_toolButtonUnselectAllTerminals_clicked()
{
    static int rowCount = m_modelTerminals->rowCount(QModelIndex());
    for(int i=0; i<rowCount; ++i){
        m_modelTerminals->setData(m_modelTerminals->index(i,0),Qt::Unchecked, Qt::CheckStateRole);
    }
}

void SelectTerminalPage::on_comboBoxRegions_activated(int idx)
{
    int ownerid = m_modelRegions->data(m_modelRegions->index(idx,0,QModelIndex())).toInt();

    qInfo(logInfo()) << "OVNER_ID =" << ownerid << "IDX" << idx;

    static int rowCount = m_modelTerminals->rowCount(QModelIndex());
    for(int i=0; i<rowCount; ++i){
        if(m_modelTerminals->data(m_modelTerminals->index(i,3,QModelIndex()),Qt::DisplayRole).toInt() == ownerid){
            m_modelTerminals->setData(m_modelTerminals->index(i,0),Qt::Checked, Qt::CheckStateRole);
        }
    }

    m_proxyModel->sort(0,Qt::DescendingOrder);
}

void SelectTerminalPage::on_toolButtonSelectAllList_clicked()
{
    const int rowSelected = ui->listWidget->count();
    QListWidgetItem *item = nullptr;
    for(int i=0; i< rowSelected; ++i ) {
        item = ui->listWidget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        highlightChecked(item);
    }
}

void SelectTerminalPage::on_toolButtonUnselectAllList_clicked()
{
    const int rowSelected = ui->listWidget->count();
    QListWidgetItem *item = nullptr;
    for(int i=0; i< rowSelected; ++i ) {
        item = ui->listWidget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        highlightChecked(item);
    }
}

#include "selectterminalpage.h"
#include "ui_selectterminalpage.h"

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
}

bool SelectTerminalPage::validatePage()
{

}

bool SelectTerminalPage::isComplete() const
{
}

int SelectTerminalPage::nextId() const
{
}

#ifndef SELECTTERMINALPAGE_H
#define SELECTTERMINALPAGE_H

#include "ModelTerminals/modelterminals.h"
#include "LoggingCategories/loggingcategories.h"
#include "CheckBoxDelegate/checkboxdelegate.h"
#include "TerminalClass/terminalclass.h"


#include <QWizardPage>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSortFilterProxyModel>
#include <QListWidgetItem>

namespace Ui {
class SelectTerminalPage;
}

class SelectTerminalPage : public QWizardPage
{
    Q_OBJECT

private slots:
    void terminalChecked();
    void highlightChecked(QListWidgetItem *item);
    void on_toolButtonAddTerm_clicked();
    void on_toolButtonSelectAllTerminals_clicked();

    void on_toolButtonUnselectAllTerminals_clicked();

    void on_comboBoxRegions_activated(int index);

    void on_toolButtonSelectAllList_clicked();

    void on_toolButtonUnselectAllList_clicked();

signals:
    void signalSendTermList(QStringList);
public:
    explicit SelectTerminalPage(QWidget *parent = nullptr);
    ~SelectTerminalPage();

private:
    Ui::SelectTerminalPage *ui;
    ModelTerminals *m_modelTerminals;
    QSortFilterProxyModel *m_proxyModel;
    CheckBoxDelegate *chekDelegate;
    QList<TerminalClass> m_listTerminals;
    QStringList m_listSelectetTerminals;
    QStringList m_terminalsGo;
    QSqlQueryModel *m_modelRegions;
private:
    void createUI();
    void createModelTerminals();
    void createListTerminals();
    void createModelRegions();

    // QWizardPage interface
public:
    void initializePage();
    bool validatePage();
    bool isComplete() const;
    int nextId() const;
};

#endif // SELECTTERMINALPAGE_H

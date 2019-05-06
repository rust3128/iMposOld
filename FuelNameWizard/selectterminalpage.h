#ifndef SELECTTERMINALPAGE_H
#define SELECTTERMINALPAGE_H

#include "ModelTerminals/modelterminals.h"
#include "LoggingCategories/loggingcategories.h"
#include "CheckBoxDelegate/checkboxdelegate.h"
#include "TerminalClass/terminalclass.h"


#include <QWizardPage>
#include <QSqlQuery>
#include <QSqlError>
#include <QSortFilterProxyModel>

namespace Ui {
class SelectTerminalPage;
}

class SelectTerminalPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SelectTerminalPage(QWidget *parent = nullptr);
    ~SelectTerminalPage();

private:
    Ui::SelectTerminalPage *ui;
    ModelTerminals *m_modelTerminals;
    QSortFilterProxyModel *m_proxyModel;
    CheckBoxDelegate *chekDelegate;
    QList<TerminalClass> m_listTerminals;
private:
    void createUI();
    void createModelTerminals();
    void createListTerminals();

    // QWizardPage interface
public:
    void initializePage();
    bool validatePage();
    bool isComplete() const;
    int nextId() const;
};

#endif // SELECTTERMINALPAGE_H

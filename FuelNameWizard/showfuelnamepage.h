#ifndef SHOWFUELNAMEPAGE_H
#define SHOWFUELNAMEPAGE_H

#include "statusthread.h"
#include <QWizardPage>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class ShowFuelNamePage;
}

class ShowFuelNamePage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ShowFuelNamePage(QWidget *parent = nullptr);
    ~ShowFuelNamePage();

public slots:
    void slotGetListTerm(QStringList list);
    void slotGetStatusThread(statusThread stTh);
private:
    Ui::ShowFuelNamePage *ui;
    QStringList m_listTerm;
    QStringList statusList;
    QList<QStringList> listConnections;
private:
    void createUI();
    void fuelNameList(QStringList connList);
    void getConnectionsInfo();

    // QWizardPage interface
public:
    void initializePage();
};

#endif // SHOWFUELNAMEPAGE_H

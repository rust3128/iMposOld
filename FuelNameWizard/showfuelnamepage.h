#ifndef SHOWFUELNAMEPAGE_H
#define SHOWFUELNAMEPAGE_H

#include "statusthread.h"
#include "GetConnectionOptionsClass/getconnectionoptionsclass.h"
#include "AzsFuelName/azsfuelname.h"
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
signals:
    void signalGoFuelName();
    void signalSendFuelNameList(QList<AzsFuelName>);
private slots:
    void slotStartConnectionsList();
    void slotAzsComplete();
    void slotStartGetFuelName();
    void slotGetConnectionsList(QList<QStringList> list);
    void slotFinishConnectionsList();
    void fuelNameList();
public slots:
    void slotGetListTerm(QStringList list);
    void slotGetStatusThread(statusThread status);
    void slotGetAzsFuelName(AzsFuelName aFN);
private:
    Ui::ShowFuelNamePage *ui;
    QStringList m_listTerm;
    QStringList statusList;
    QList<QStringList> listConnections;
    statusThread stTh;
    QList<AzsFuelName> listFuelName;
    bool isWorkComplete;
    int colWorkTerm;
private:
    void createUI();
    void statusConnectToDatabase();
    void statusSelectFuelName();
    void statusErrorConnectDatabase();
    void statusFinished();


    // QWizardPage interface
public:
    void initializePage();

    // QWizardPage interface
public:
    bool validatePage();

    // QWizardPage interface
public:
    bool isComplete() const;
};

#endif // SHOWFUELNAMEPAGE_H

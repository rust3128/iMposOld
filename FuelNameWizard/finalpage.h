#ifndef FINALPAGE_H
#define FINALPAGE_H

#include "GetConnectionOptionsClass/getconnectionoptionsclass.h"
#include "AzsFuelName/azsfuelname.h"
#include "LoggingCategories/loggingcategories.h"
#include <QWizardPage>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>


namespace Ui {
class FinalPage;
}

class FinalPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit FinalPage(QWidget *parent = nullptr);
    ~FinalPage();
public slots:
    void slotGetListFuelName(QList<AzsFuelName> lFN);

private:
    Ui::FinalPage *ui;
    QList<AzsFuelName> m_listFuelName;
    QTextDocument *document;
    QPrinter printer;
    QStringList headers;
private:
    void createUI();
    void viewFuelName();

    // QWizardPage interface
public:
    void initializePage();
private slots:
    void on_pushButtonPrint_clicked();
    void printPreviewNeeds(QPrinter*);
    void on_pushButtonXls_clicked();
};

#endif // FINALPAGE_H

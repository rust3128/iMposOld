#ifndef SHOWFUELNAMEPAGE_H
#define SHOWFUELNAMEPAGE_H

#include <QWizardPage>

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
    void slotStartGetFuel();
private:
    Ui::ShowFuelNamePage *ui;
    QStringList m_listTerm;
private:
    void createUI();
    void fuelNameList(QString terminal);

    // QWizardPage interface
public:
    void initializePage();
};

#endif // SHOWFUELNAMEPAGE_H

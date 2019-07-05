#ifndef SETFUELNAMEPAGE_H
#define SETFUELNAMEPAGE_H

#include <QWizardPage>
#include <QSqlTableModel>
#include <QListWidgetItem>

namespace Ui {
class SetFuelNamePage;
}

class SetFuelNamePage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SetFuelNamePage(QWidget *parent = nullptr);
    ~SetFuelNamePage();
private slots:


    void on_groupBoxDT_clicked();

    void on_groupBoxVIP_clicked();

    void on_checkBoxDTS_clicked();

    void on_checkBoxDTW_clicked();

    void on_checkBoxVIPS_clicked();

    void on_checkBoxVIPW_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::SetFuelNamePage *ui;
    QSqlTableModel *modelFuel;
private:
    void createUI();


    // QWizardPage interface
public:
    void initializePage();
    bool validatePage();
    bool isComplete() const;
    int nextId() const;
};

#endif // SETFUELNAMEPAGE_H

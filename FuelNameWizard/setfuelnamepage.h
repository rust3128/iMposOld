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
    void highlightChecked(QListWidgetItem *item);
private:
    Ui::SetFuelNamePage *ui;
    QSqlTableModel *modelFuel;
private:
    void createUI();
    void createModels();

    // QWizardPage interface
public:
    void initializePage();
    bool validatePage();
    bool isComplete() const;
    int nextId() const;
};

#endif // SETFUELNAMEPAGE_H

#ifndef SETFUELNAMEPAGE_H
#define SETFUELNAMEPAGE_H

#include <QWizardPage>

namespace Ui {
class SetFuelNamePage;
}

class SetFuelNamePage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SetFuelNamePage(QWidget *parent = nullptr);
    ~SetFuelNamePage();

private:
    Ui::SetFuelNamePage *ui;

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

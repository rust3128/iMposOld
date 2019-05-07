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

private:
    Ui::ShowFuelNamePage *ui;
private:
    void createUI();
};

#endif // SHOWFUELNAMEPAGE_H

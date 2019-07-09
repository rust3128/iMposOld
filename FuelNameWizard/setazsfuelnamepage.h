#ifndef SETAZSFUELNAMEPAGE_H
#define SETAZSFUELNAMEPAGE_H

#include <QWizardPage>

namespace Ui {
class SetAzsFuelNamePage;
}

class SetAzsFuelNamePage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SetAzsFuelNamePage(QWidget *parent = nullptr);
    ~SetAzsFuelNamePage();

private:
    void createUI();
private:
    Ui::SetAzsFuelNamePage *ui;
};

#endif // SETAZSFUELNAMEPAGE_H

#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QWizardPage>
#include <QSqlTableModel>

namespace Ui {
class IntroPage;
}

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit IntroPage(QWidget *parent = nullptr);
    ~IntroPage();

private:
    Ui::IntroPage *ui;
    QSqlTableModel *modelFuel;
private:
    void createUI();
    void createModels();

    // QWizardPage interface
public:
    void initializePage();
    bool isComplete() const;
private slots:
    void on_radioButtonView_clicked();
    void on_radioButtonEdit_clicked();
};

#endif // INTROPAGE_H

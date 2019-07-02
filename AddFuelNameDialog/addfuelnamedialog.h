#ifndef ADDFUELNAMEDIALOG_H
#define ADDFUELNAMEDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>


namespace Ui {
class AddFuelNameDialog;
}

class AddFuelNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFuelNameDialog(int row, QWidget *parent = nullptr);
    ~AddFuelNameDialog();

signals:
    void signalReady();

private slots:
    void on_lineEditFuelName_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::AddFuelNameDialog *ui;
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;
private:
    void setupModel();
    void createUI();
};

#endif // ADDFUELNAMEDIALOG_H

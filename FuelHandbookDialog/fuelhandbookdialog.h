#ifndef FUELHANDBOOKDIALOG_H
#define FUELHANDBOOKDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class FuelHandbookDialog;
}

class FuelHandbookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FuelHandbookDialog(QWidget *parent = nullptr);
    ~FuelHandbookDialog();

private slots:
    void slotUpdateModels();

    void on_pushButtonAdd_clicked();



    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButtonClose_clicked();

private:
    Ui::FuelHandbookDialog *ui;
    QSqlTableModel *modelName;
private:
    void createUI();
    void createModel();
};

#endif // FUELHANDBOOKDIALOG_H

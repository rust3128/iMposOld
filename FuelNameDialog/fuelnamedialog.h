#ifndef FUELNAMEDIALOG_H
#define FUELNAMEDIALOG_H

#include "LoggingCategories/loggingcategories.h"
#include "CheckBoxDelegate/checkboxdelegate.h"
#include "FuelNameDialog/terminalclass.h"
#include "modelterminals.h"

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QAbstractTableModel>

namespace Ui {
class FuelNameDialog;
}

class FuelNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FuelNameDialog(QWidget *parent = nullptr);
    ~FuelNameDialog();

private:
    Ui::FuelNameDialog *ui;
    ModelTerminals *modelTerminals;
    CheckBoxDelegate *checkDelegate;
    QList<TerminalClass> listTerminals;
private:
    void createModelterminals();
    void createListTerminals();

};

#endif // FUELNAMEDIALOG_H

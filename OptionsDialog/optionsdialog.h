#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <GetOptionsData/getoptionsdata.h>
#include <QDialog>


namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();
    bool getIsCritical();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_checkBox1000_clicked();

    void slotGroupBoxChanged();

private:
    Ui::OptionsDialog *ui;
    GetOptionsData *options;
    QList<option> listOptions;
    QList<option> currentListOptions;
    option opt;
    bool m_isCritical;
private:
    void createUI();
    void createConnections();
};

#endif // OPTIONSDIALOG_H

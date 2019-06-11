#include "finalpage.h"
#include "ui_finalpage.h"

#include <QTableWidgetItem>
#include <QFileDialog>
#include <QDateTime>
#include <QDesktopServices>

#include "xlsxdocument.h"
#include "xlsxformat.h"
//#include "xlsxchartsheet.h"
//#include "xlsxcellrange.h"
//#include "xlsxchart.h"
//#include "xlsxrichstring.h"
//#include "xlsxworkbook.h"

using namespace QXlsx;


FinalPage::FinalPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::FinalPage)
{
    ui->setupUi(this);

    this->setFinalPage(true);
    createUI();
}

FinalPage::~FinalPage()
{
    delete ui;
}

void FinalPage::slotGetListFuelName(QList<AzsFuelName> lFN)
{
    m_listFuelName = lFN;
}

void FinalPage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Заключительный шаг.</span></p></body></html>");
//    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Выберите терминалы (АЗС) для который необходимо произвести с наименованиями видов топлива.</span></p></body></html>");
    ui->frameName->hide();
}



void FinalPage::initializePage()
{
    if(field("checkView").toBool()){
        viewFuelName();
    }
}

void FinalPage::viewFuelName()
{

    headers <<"Резервуар"<<"Код"<<"Кратко"<<"Полное";
    ui->frameName->show();
    ui->tableWidgetName->setColumnCount(4);
    ui->tableWidgetName->setHorizontalHeaderLabels(headers);
    ui->tableWidgetName->verticalHeader()->hide();
    int colAzs = m_listFuelName.size();
    for(int i = 0; i<colAzs; ++i ){
        int row = ui->tableWidgetName->rowCount();
        ui->tableWidgetName->insertRow(row);
        QTableWidgetItem *itemAZS = new QTableWidgetItem(QString::number(m_listFuelName.at(i).getTerminalID()));
        itemAZS->setTextAlignment(Qt::AlignHCenter);

        itemAZS->setBackgroundColor(QColor("#aaff7f"));
//        itemAZS->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidgetName->setSpan(row,0,1,4);
        ui->tableWidgetName->setItem(row,0,itemAZS);
        for(int j = 0; j<m_listFuelName.at(i).getListFuel().size();++j){
            int rowName = ui->tableWidgetName->rowCount();
            ui->tableWidgetName->insertRow(rowName);
            ui->tableWidgetName->setItem(rowName,0, new QTableWidgetItem(QString::number(m_listFuelName.at(i).getListFuel().at(j).getTankID())));
            ui->tableWidgetName->item(rowName,0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetName->setItem(rowName,1, new QTableWidgetItem(QString::number(m_listFuelName.at(i).getListFuel().at(j).getFuelID())));
            ui->tableWidgetName->item(rowName,1)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetName->setItem(rowName,2, new QTableWidgetItem(m_listFuelName.at(i).getListFuel().at(j).getShortName()));
            ui->tableWidgetName->setItem(rowName,3, new QTableWidgetItem(m_listFuelName.at(i).getListFuel().at(j).getName()));
            ui->tableWidgetName->resizeColumnsToContents();
        }

    }
    ui->tableWidgetName->verticalHeader()->setDefaultSectionSize(ui->tableWidgetName->verticalHeader()->minimumSectionSize());
}

void FinalPage::on_pushButtonPrint_clicked()
{
    QString printStr;
    QTextStream out(&printStr);

    const int rowCount = ui->tableWidgetName->rowCount();
    const int columnCount = 4;

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=utf-8\">\n"
        <<  QString("<title>%1</title>\n").arg("refTitleName")
        <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<tr bgcolor=#f0f0f0>";

    for(int column = 0; column < columnCount; column++)
        out << QString("<th>%1</th>").arg(ui->tableWidgetName->horizontalHeaderItem(column)->text());
    out << "</tr>\n";
    for(int row = 0; row < rowCount; row++){
        out << "<tr>";
        for(int column = 0; column < columnCount; column++){
//            qInfo(logInfo()) << "Row" << row << "Column" << column << "ColumnCpan" << ui->tableWidgetName->columnSpan(row, column);
            if(ui->tableWidgetName->columnSpan(row,0) != 1){
                out << QString("<td bkcolor=0 colspan = 4 align='center' bgcolor='#FBF0DB'>%1</td>").arg(ui->tableWidgetName->item(row,0)->text());
                break;
            } else{
                out << QString("<td>%1</td>").arg(ui->tableWidgetName->item(row,column)->text());
            }
        }
        out << "</tr>";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";
    document = new QTextDocument();

    document->setHtml(printStr);




   QPrintPreviewDialog  *prDialog = new QPrintPreviewDialog(&printer, this);
   connect(prDialog,SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreviewNeeds(QPrinter*)));

    prDialog->showMaximized();
    prDialog->exec();

}

void FinalPage::printPreviewNeeds(QPrinter *)
{
    document->print(&printer);
}

void FinalPage::on_pushButtonXls_clicked()
{
    Document xlsx;
    Format format;
    Format formatMerge;


    format.setHorizontalAlignment(Format::AlignHCenter);
    format.setVerticalAlignment(Format::AlignVCenter);
    formatMerge.setPatternBackgroundColor(QColor("#aaff7f"));
    formatMerge.setHorizontalAlignment(Format::AlignHCenter);
    formatMerge.setVerticalAlignment(Format::AlignVCenter);
    xlsx.setColumnWidth(1,10);
    xlsx.setColumnWidth(4,30);
    static int columnCount = headers.size();
    const int rowCount = ui->tableWidgetName->rowCount();
    for(int i =0; i<columnCount; ++i){
        xlsx.write(1,i+1, headers.at(i),format);
    }
    for(int row=0; row<rowCount; ++row){
        for(int column = 0; column < columnCount; ++column){
            if(ui->tableWidgetName->columnSpan(row,0) != 1){
                xlsx.write(row+2, column+1, ui->tableWidgetName->item(row,0)->text());
                CellRange cellRange = CellRange(row+2,column+1,row+2,columnCount);
                xlsx.mergeCells(cellRange, formatMerge);

                break;
            } else {
                xlsx.write(row+2,column+1,ui->tableWidgetName->item(row,column)->text(),format);
            }
        }
    }





    QString curPath = QDir::currentPath();
    QString fileName = "ListFuels"+QDateTime::currentDateTime().toString("yyyyMMdd");

    QString fileNameFull = QFileDialog::getSaveFileName(this,"Сохранить скрипт",curPath+"//"+fileName+".xlsx",
                                               "XLSX file (*.xlsx);;Все файлы (*.*)");

    xlsx.saveAs(fileNameFull); // save the document as 'Test.xlsx'
    QString oU = "file://"+fileNameFull;
    QDesktopServices::openUrl(QUrl(oU, QUrl::TolerantMode));

}

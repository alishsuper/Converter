#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag=0; flag1=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_clicked() {
    //входной файл
    fileIn=QFileDialog::getOpenFileName(this,tr("OpenFile"),"",
                                        tr("SNP Files (*.s1p *.s2p *.s3p *.s4p);;CITIfiles (*.dat *.cti *.citi *.unc)"));
     if (!fileIn.isEmpty()){
        flag = f.checkForFileType(fileIn);
        if (flag==1){
            snp.scanDocument(fileIn);
        }else {
            citi.scanDocument(fileIn);
        }
    }
}

void MainWindow::on_saveAs_clicked() {
    if (fileIn != ""){
        //выходной файл
        fileOut=QFileDialog::getSaveFileName(this,tr("Save File"),"",
                                                      tr("SNP Files (*.s1p *.s2p *.s3p *.s4p);;CITIfiles (*.dat *.cti *.citi *.unc)"));
        if (ui->DB->isChecked()){
            flag_format2="DB";
        } else if (ui->MA->isChecked()){
            flag_format2="MA";
        } else {
            flag_format2="RI";
        }
        if (fileOut != ""){
            flag1=f.checkForFileType(fileOut);
            //snp->citi
            if (flag==1&&flag1==0) {
                snp.writeDocument(fileOut);
            //snp->snp с однинаковыми форматами данных
            } else if (flag==1&&flag1==1&&!flag_format2.compare(snp.getflagformat(), Qt::CaseInsensitive)){
                fileOut.replace((fileOut.length()-2),2,f.checkForNumbParam(f.checkForPort(fileIn)));
                f.writeWithoutChange(fileIn, fileOut);
            //snp->snp с разными форматами данных
            } else if (flag==1&&flag1==1&&flag_format2.compare(snp.getflagformat(), Qt::CaseInsensitive)){
                fileOut.replace((fileOut.length()-2),2,f.checkForNumbParam(f.checkForPort(fileIn)));
                snp.writeWithChange(fileIn, fileOut, flag_format2);
            // citi->snp
            } else if (flag==0&&flag1==1){
                fileOut.replace((fileOut.length()-2),2,f.checkForNumbParam(citi.getnumberofparam()));
                citi.writeDocument(fileOut, flag_format2);
            }
        }
    }
}

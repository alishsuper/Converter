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
    filein=QFileDialog::getOpenFileName(this,tr("OpenFile"),"",
                                        tr("SNP Files (*.s1p *.s2p *.s3p *.s4p);;CITIfiles (*.dat *.cti *.citi *.unc)"));
     if (!filein.isEmpty()){
        flag = f.checkForFileType(filein);
        if (flag==1){
            snp.scanDocument(filein);
        }else {
            citi.scanDocument(filein);
        }
    }
}

void MainWindow::on_saveAs_clicked() {
    if (filein != ""){
        //выходной файл
        fileout=QFileDialog::getSaveFileName(this,tr("Save File"),"",
                                                      tr("SNP Files (*.s1p *.s2p *.s3p *.s4p);;CITIfiles (*.dat *.cti *.citi *.unc)"));
        if (ui->DB->isChecked()){
            flag_format2="DB";
        } else if (ui->MA->isChecked()){
            flag_format2="MA";
        } else {
            flag_format2="RI";
        }
        if (fileout != ""){
            flag1=f.checkForFileType(fileout);
            //snp->citi
            if (flag==1&&flag1==0) {
                snp.writeDocument(fileout);
            //snp->snp с однинаковыми форматами данных
            } else if (flag==1&&flag1==1&&!flag_format2.compare(snp.getflagformat(), Qt::CaseInsensitive)){
                fileout.replace((fileout.length()-2),2,f.checkForNumbParam(f.checkForPort(filein)));
                f.writeWithoutChange(filein, fileout);
            //snp->snp с разными форматами данных
            } else if (flag==1&&flag1==1&&flag_format2.compare(snp.getflagformat(), Qt::CaseInsensitive)){
                fileout.replace((fileout.length()-2),2,f.checkForNumbParam(f.checkForPort(filein)));
                snp.writeWithChange(filein, fileout, flag_format2);
            // citi->snp
            } else if (flag==0&&flag1==1){
                fileout.replace((fileout.length()-2),2,f.checkForNumbParam(citi.getnumberofparam()));
                citi.writeDocument(fileout, flag_format2);
            }
        }
    }
}

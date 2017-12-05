#ifndef SNP_H
#define SNP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <functions.h>

class SNP
{
private:
    int flagfreq;
    int flagport;
    QString flagparam;
    QString flag_format1;
    int numboffreq;
    int numbofparam;
    Functions f;
    QFile file_in;
    QFile file_out;
    QVector<QString> tempVector;
    QVector<QString> freq;
    QStringList list;
    int number;// количество элементов в строчке с s параметрами

public:
    SNP();
    void scanDocument(QString filein);
    QString gettempVector(int i){
        return tempVector.value(i);
    }
    void removetempVector(int n){
        tempVector.remove(0,n);
    }
    QString getfreq(int i){
        return freq.value(i);
    }
    void removefreg(int n){
        freq.remove(0,n);
    }
    int getflagnumber(){
        return 2*flagport;
    }
    QString getflagformat(){
        return flag_format1;
    }
    void writeWithChange(QString filein, QString fileout, QString flag_format2);
    void writeDocument(QString fileout);
};

#endif // SNP_H

#ifndef CITIFILE_H
#define CITIFILE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <functions.h>
#include <snp.h>
#include <QTextStream>

class CitiFile
{
private:
    Functions f;
    SNP snp;
    QFile file_in;
    QFile file_out;
    QVector<QString> tempVector;
    QVector<QString> freq;
    QStringList list;
    int numboffreq;
    int numbofparam;
    int s;//количество s параметров
    int size;
    QString flag_format1;

public:
    CitiFile();
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
    int getnumberofparam(){
        return s;
    }
    void writeDocument(QString fileout, QString flag_format);
};

#endif // CITIFILE_H

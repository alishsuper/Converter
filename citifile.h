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
    QFile file_in;
    QFile file_out;
    QVector<QString> tempVector;
    QVector<QString> freq;
    QStringList list;
    int numb_of_freq;
    int numb_of_param;
    int s;//количество s параметров
    int size;
    QString flag_format_in;
    QString gettempVector(int i) const{
        return tempVector.value(i);
    }
    void removetempVector(){
        tempVector.resize(0);
    }
    QString getfreq(int i) const{
        return freq.value(i);
    }
    void removefreg(){
        freq.resize(0);
    }

public:
    CitiFile();
    void scanDocument(QString filein);
    int getnumberofparam() const{
        return s;
    }
    void writeDocument(QString fileOut, QString flag_format);
};

#endif // CITIFILE_H

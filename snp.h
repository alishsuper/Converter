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
    int flag_freq;
    int flag_port;
    QString flag_param;
    QString flag_format1;
    int numb_of_freq;
    int numb_of_param;
    Functions f;
    QFile file_in;
    QFile file_out;
    QVector<QString> tempVector;
    QVector<QString> freq;
    QStringList list;
    int number;// количество элементов в строчке с s параметрами
    QString f_str;//переменные для
    int f_int;    //преобразования
    double f_double; //частот(kHz,MHz,GHz->Hz)
    void removetempVector(int n){
        tempVector.remove(0,n);
    }

public:
    SNP();
    void scanDocument(QString filein);
    QString gettempVector(int i) const{
        return tempVector.value(i);
    }
    QString getfreq(int i) const{
        return freq.value(i);
    }
    void removefreg(int n){
        freq.remove(0,n);
    }
    int getflagnumber() const{
        return 2*flag_port;
    }
    QString getflagformat() const{
        return flag_format1;
    }
    void writeWithChange(QString filein, QString fileout, QString flag_format2);
    void writeDocument(QString fileout);
};

#endif // SNP_H

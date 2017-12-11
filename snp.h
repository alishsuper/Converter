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
    QString flag_format_in;
    int numb_of_freq;
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
    SNP();
    void scanDocument(QString filein);
    int getflagnumber() const{
        return 2*flag_port;
    }
    QString getflagformat() const{
        return flag_format_in;
    }
    void writeWithChange(QString filein, QString fileout, QString flag_format_out);
    void writeDocument(QString fileout);
};

#endif // SNP_H

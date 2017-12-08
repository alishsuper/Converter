#include "snp.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QQueue>
#include <QList>
#include <QtMath>

SNP::SNP(){
    flag_freq=0; flag_param="S"; flag_format1="DB"; flag_port=1;
}

void SNP::scanDocument(QString filein){
    removefreg(numb_of_freq);
    removetempVector(numb_of_param);
    qDebug() << tempVector.size();
    qDebug() << numb_of_param;

    QTextStream in(&(file_in));
    file_in.setFileName(filein);
    if (!file_in.open(QIODevice::ReadOnly)){
       qDebug() << "File don't open!";
    }
    QString infoline = in.readLine();
    while (!infoline.contains("#")){//считываем пока не считаем информативную строку
        infoline = in.readLine();
    }
    //check for unit of frequency
    flag_freq = f.checkForFreg(infoline);
    //check for kind of network parameter
    flag_param = f.checkForParam(infoline);
    //check for format of network parameter
    flag_format1 = f.checkForFormat(infoline);
    //check for number of port
    flag_port = f.checkForPort(filein);

    numb_of_freq=0; numb_of_param=0;
    while(!in.atEnd()){
        infoline = in.readLine();
        list = infoline.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        number = list.count();//number of elements in the row
        if (!infoline.contains("!")){
            if(number%2!=0){
                numb_of_freq++;//number of frequency
                if (infoline.contains("+")){
                    f_int=list[0].split("+")[1].toInt();
                    f_int=f_int+flag_freq;
                    f_str=list[0].split("+")[0]+"+0"+QString::number(f_int);
                    freq.push_back(f_str);
                } else{
                    f_double=list[0].toDouble();
                    f_double=f_double*qPow(10, flag_freq);
                    f_str=QString::number(f_double);
                    freq.push_back(f_str);
                }
                for (int i=1; i<number; i++){
                    tempVector.push_back(list[i]);
                    numb_of_param++;
                }
            }else{
                for (int i=0; i<number; i++){
                    tempVector.push_back(list[i]);
                    numb_of_param++;
                }
            }
        }
    }
    qDebug() << tempVector.size();
    qDebug() << numb_of_param;
    file_in.close();
}

//snp->citi
void SNP::writeDocument(QString fileout)
{
    QTextStream out(&file_out);
    file_out.setFileName(fileout);
     if (!file_out.open(QIODevice::WriteOnly)) {
         qDebug() << "File don't open!";
     } else {
             out << "VAR FREQ MAG "+QString::number(numb_of_freq)+"\r\n";
             //заполнение данных с DATA (DATA DB S11 и т.д.)
             for (int i=1; i<qSqrt(flag_port)+1; i++){
                for (int j=1; j<qSqrt(flag_port)+1; j++){
                    out << "DATA "+flag_param+QString::number(i)+QString::number(j)+" "+getflagformat()+"\r\n";
                }
             }
             out << "VAR_LIST_BEGIN\r\n";
             // вывод частот
             for (int i=0; i<numb_of_freq; i++){
                  out << getfreq(i)+"\r\n";
             }
             out << "VAR_LIST_END\r\n";
             for (int i=0; i<flag_port; i++){
                 out << "BEGIN\r\n";
                 for (int j=0; j<numb_of_freq; j++){
                     out << gettempVector(j*getflagnumber()+2*i)+"," << gettempVector(j*getflagnumber()+1+2*i)+"\r\n";
                 }
                 out << "END\r\n";
             }
             out.flush();
             file_out.close();
    }
}

//snp->snp
void SNP::writeWithChange(QString filein, QString fileout, QString flag_format2)
{
    QTextStream in(&(file_in));
    file_in.setFileName(filein);
    QTextStream out(&file_out);
    if (filein==fileout){
        file_out.setFileName(fileout+"p");
    } else {
        file_out.setFileName(fileout);
    }
    if (!file_out.open(QIODevice::WriteOnly)) {
        qDebug() << "File don't open!";
    }
    QString infoline; QStringList list;
    if (!file_in.open(QIODevice::ReadOnly)){
       qDebug() << "File don't open!";
    } else {
        while(!in.atEnd()){
            infoline = in.readLine();
            if(infoline.contains("!")){
                out << infoline+"\r\n";
            } else if(infoline.contains("#")){
                infoline.replace(QString(" " + flag_format1), QString(" " + flag_format2), Qt::CaseInsensitive);
                out << infoline+"\r\n";
            } else{
                list=infoline.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                int size=0, number=0;
                number=list.count();
                size=list[0].size();
                int z=1;
                if(number%2==0){
                    for (int k=0; k<=size; k++){ out << " ";}// вставка пробелов перед s параметрами
                    z=0;
                } else {
                    out << list[0]+" ";
                }
                for (int i=z; i<number; i=i+2){
                    out << f.convertFormat(list[i].toDouble(), list[i+1].toDouble(), flag_format1, flag_format2);
                }
                out << "\r\n";
            }
        }
        file_in.close(); file_out.close();
        if (filein==fileout){
            f.writeWithoutChange(fileout+"p", fileout);
            //удаляем ненужный файл
            QFile::setPermissions(fileout+"p", QFile::ReadOwner | QFile::WriteOwner);
            QFile::remove(fileout+"p");
        }
    }
}

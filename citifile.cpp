#include "citifile.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QQueue>
#include <QList>
#include <QtMath>

CitiFile::CitiFile(){
    numb_of_freq=0; flag_format_in="DB";
}

void CitiFile::scanDocument(QString filein)
{
    removefreg();
    removetempVector();

    //входной файл
    QTextStream in(&file_in);
    file_in.setFileName(filein);
    if (!file_in.open(QIODevice::ReadOnly)){
       qDebug() << "File don't open!";
    }

    QString data_line = in.readLine();
    while (!data_line.contains("VAR ", Qt::CaseInsensitive)){//считываем пока не попадет строчка с VAR
        data_line = in.readLine();
    }
    int number=0;//номер числа в строке VAR
    while(data_line.split(" ")[number].toInt()==0){
        number++;
    }
    numb_of_freq = data_line.split(" ")[number].toInt();
    data_line = in.readLine();
    s=0;
    while (!data_line.contains("BEGIN")){
        if (data_line.contains("DATA")){
            flag_format_in=f.checkForFormat(data_line);
            s++;//получили количесто s параметров
        }
        data_line = in.readLine();
    }
    for (int j=0; j<numb_of_freq; j++){
        freq.push_back(in.readLine());//получаем частоты
    }
    in.readLine();//удаляем VAR_LIST_END
    QString s_parameter="";//строка для считывания s параметров
    for (int j=0; j<s; j++){
        s_parameter=in.readLine();
        for (int i=0; i<numb_of_freq; i++){
            s_parameter=in.readLine();//получили s параметры
            list=s_parameter.split(QRegExp(","), QString::SkipEmptyParts);
            tempVector.push_back(list[0]);
            tempVector.push_back(list[1]);
        }
        s_parameter=in.readLine();//считали END
    }
    file_in.close();
}

void CitiFile::writeDocument(QString fileOut, QString flag_format_out)
{
    QTextStream out(&file_out);
    file_out.setFileName(fileOut);
     if (!file_out.open(QIODevice::WriteOnly)) {
         qDebug() << "File don't open!";
     } else {
         out << "# Hz S "+flag_format_out+" R 50\r\n";
         int d=sqrt(s);
         for (int i=0; i<numb_of_freq; i++){
             out << getfreq(i)+" ";
             size = getfreq(i).size();
             if (s<9){
                 for (int j=0; j<s; j++){
                     if (flag_format_in.compare(flag_format_out, Qt::CaseInsensitive)){
                         out << f.convertFormat(gettempVector(2*i+j*numb_of_freq*2).toDouble(), gettempVector(2*i+j*numb_of_freq*2+1).toDouble(), flag_format_in, flag_format_out);
                     }else{
                         out << gettempVector(2*i+j*numb_of_freq*2)+" "+gettempVector(2*i+j*numb_of_freq*2+1)+" ";
                     }
                 }
             }else{
                 int r=0;
                 for (int j=0; j<d; j++){
                     out << gettempVector(2*i+r*numb_of_freq*2)+" "+gettempVector(2*i+r*numb_of_freq*2+1)+" ";
                     r++;
                 }
                 for (int l=0; l<d-1; l++){
                     out <<"\r\n";
                     for (int k=0; k<=size; k++){ out << " ";}// вставка пробелов перед s параметрами
                     for (int z=0; z<d; z++){
                         out << gettempVector(2*i+r*numb_of_freq*2)+" "+gettempVector(2*i+1+r*numb_of_freq*2)+" ";
                         r++;
                     }
                 }
             }
             out <<"\r\n";
         }
         out.flush();
         file_out.close();
     }
}

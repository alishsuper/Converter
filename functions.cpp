#include "functions.h"
#include <QDebug>
#include <QtMath>

Functions::Functions()
{
}

QString Functions::checkForFormat(QString line)
{
   if(line.contains(" DB", Qt::CaseInsensitive)) {
        return "DB";
   } else if(line.contains(" RI", Qt::CaseInsensitive)) {
        return "RI";
   } else {
        return "MA";
   }
}

int Functions::checkForFreg(QString infoline)
{
    if(infoline.contains(" Hz ", Qt::CaseInsensitive)) {
        return 0;
    } else if(infoline.contains(" kHz ", Qt::CaseInsensitive)) {
        return 3;
    } else if(infoline.contains(" MHz ", Qt::CaseInsensitive)) {
        return 6;
    } else {
        return 9;
    }
}

QString Functions::checkForParam(QString infoline)
{
    if(infoline.contains(" S ", Qt::CaseInsensitive)) {
        return "S";
    } else if(infoline.contains(" Y ", Qt::CaseInsensitive)) {
        return "Y";
    } else if(infoline.contains(" Z ", Qt::CaseInsensitive)) {
        return "Z";
    } else if(infoline.contains(" H ", Qt::CaseInsensitive)) {
        return "H";
    } else {
        return "G";
    }
}

int Functions::checkForPort(QString filein)
{
    int flagport;
    if (filein.contains(".s1p")) {
        flagport = 1;
    } else if (filein.contains(".s2p")) {
        flagport = 4;
    } else if (filein.contains(".s3p")) {
        flagport = 9;
    } else {
        flagport = 16;
    }
    return flagport;
}

int Functions::checkForFileType(QString filename)
{
    int flag=0;
    if (filename.contains(".s1p", Qt::CaseInsensitive)||filename.contains(".s2p", Qt::CaseInsensitive)
            ||filename.contains(".s3p", Qt::CaseInsensitive)||filename.contains(".s4p", Qt::CaseInsensitive)){
        flag=1;
    }
    return flag;
}

void Functions::writeWithoutChange(QString filein, QString fileout)
{
    QTextStream in(&(file_in));
    QString infoline;
    file_in.setFileName(filein);
    if (!file_in.open(QIODevice::ReadOnly)){
       qDebug() << "File don't open!";
    } else {
        infoline = in.readAll();
        file_in.close();
    }
    QTextStream out(&file_out);
    file_out.setFileName(fileout);
    if (!file_out.open(QIODevice::WriteOnly)) {
        qDebug() << "File don't open, you are stupid dude!";
    } else {
        out << infoline;
        file_out.close();
    }
}

QString Functions::convertFormat(double ReState1, double ImState1, QString flag_format1, QString flag_format2)
{
    if(!flag_format1.compare("DB", Qt::CaseInsensitive) && flag_format2=="MA"){
        //db->ma
        ReState2=qPow(10, ReState1/20);
        ImState2=ImState1;
    } else if(!flag_format1.compare("DB", Qt::CaseInsensitive) && flag_format2=="RI"){
        //db->ri
        ReState2=qPow(10, ReState1/20)*qCos(ImState1);
        ImState2=qPow(10, ReState1/20)*qSin(ImState1);
    }

    if(!flag_format1.compare("RI", Qt::CaseInsensitive) && flag_format2=="DB"){
        //ri->db
        ReState2=20*log10(qSqrt(qPow(ReState1, 2)+qPow(ImState1, 2)));
        ImState2=qAtan2(ImState1, ReState1);
    } else if(!flag_format1.compare("RI", Qt::CaseInsensitive) && flag_format2=="MA"){
        //ri->ma
        ReState2=(qSqrt(qPow(ReState1, 2)+qPow(ImState1, 2)));
        ImState2=qRadiansToDegrees( qAtan2(ImState1, ReState1));
    }

    if(!flag_format1.compare("MA", Qt::CaseInsensitive) && flag_format2=="DB"){
        //ma->db
        ReState2=20*log10(ReState1);
        ImState2=ImState1;
    } else if(!flag_format1.compare("MA", Qt::CaseInsensitive) && flag_format2=="RI"){
        //ma->ri
        ReState2=ReState1*qCos(qDegreesToRadians(ImState1));
        ImState2=ReState1*qSin(qDegreesToRadians(ImState1));
    }
    return QString::number(ReState2)+" " + QString::number(ImState2)+" ";
}

QString Functions::checkForNumbParam(int numbofparam)
{
    if (numbofparam==1){
        return "1p";
    } else if (numbofparam==4){
        return "2p";
    } else if (numbofparam==9){
        return "3p";
    } else {
        return "4p";
    }
}



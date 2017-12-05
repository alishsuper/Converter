#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFile>

class Functions
{
private:
    QFile file_in;
    QFile file_out;
    double ReState2;
    double ImState2;

public:

    Functions();

    QString checkForFormat(QString line);
    int checkForFreg(QString infoline);
    QString checkForParam(QString infoline);
    int checkForPort(QString filein);
    int checkForFileType(QString filename);

    void writeWithoutChange(QString filein, QString fileout);
    QString convertFormat(double ReState1, double ImState1, QString flag_format1, QString flag_format2);
    QString checkForNumbParam(int numbofparam);
};

#endif // FUNCTIONS_H

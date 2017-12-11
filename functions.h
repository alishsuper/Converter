#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFile>

class Functions
{
public:
    Functions();

    static QString checkForFormat(QString infoline);
    static int checkForFreg(QString infoline);
    static QString checkForParam(QString infoline);
    static int checkForPort(QString filein);
    static int checkForFileType(QString filename);

    static void writeWithoutChange(QString filein, QString fileout);
    static QString convertFormat(double ReState1, double ImState1, QString flag_format_in, QString flag_format_out);
    static QString checkForNumbParam(int numbofparam);
};

#endif // FUNCTIONS_H

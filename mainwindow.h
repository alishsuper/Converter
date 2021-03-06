#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <snp.h>
#include <citifile.h>
#include <functions.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_saveAs_clicked();
    void on_openFile_clicked();

private:
    Ui::MainWindow *ui;
    SNP snp;
    CitiFile citi;
    Functions f;

    QString fileIn;
    QString fileOut;
    QString infoline;
    int flag;
    int flag1;
    QString flag_format_out;
};

#endif // MAINWINDOW_H

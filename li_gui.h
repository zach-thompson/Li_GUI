#ifndef LI_GUI_H
#define LI_GUI_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QThread>
#include <QFileDialog>
//#include "Li_files/algorithm.cpp"

class workThread : public QObject {
    Q_OBJECT

public:
    //create algorithm object here

public slots:
    void algorithm(QString path, QString savePath) {
        qDebug() << "algorithm reached";
        qDebug() << "Path: " << path;
        qDebug() << "Save path: " << savePath;
        //mor_processing::Algorithm  alg(15, 15, path, savePath);
        //alg.run();
    }

signals:

};

namespace Ui { class Li_GUI; }

class Li_GUI : public QMainWindow
{
    Q_OBJECT

public:
    QThread runThread;
    Li_GUI(QWidget *parent = nullptr);
    ~Li_GUI();

private slots:
    void on_browseButton_clicked();
    QString getPath(QString qPath);
    void on_browseButton_2_clicked();
    QString getSavePath(QString savePath);
    void on_runButton_clicked();

signals:
    void gotPath(QString qPath);
    void gotSavePath(QString savePath);
    void runPressed(QString qPath, QString savePath); // Connected to

private:
    Ui::Li_GUI *ui;
    QString qPath;
    QString savePath;
};
#endif // LI_GUI_H

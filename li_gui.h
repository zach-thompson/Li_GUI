#ifndef LI_GUI_H
#define LI_GUI_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QThread>
//#include "C/algorithm.cpp"
//#include "C/run_algorithm.sh"

class workThread : public QObject {
    Q_OBJECT

public slots:
    void algorithm(std::string path) {
        // run_algorithm.sh with argument "path"
        QString ran("Done");

        qDebug() << "Done";
        emit ranAlgorithm(ran);
    }

signals:
    void ranAlgorithm(QString &ran);
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
    void on_runButton_clicked();
    std::string readPath();
    void didItWork(QString &ran);

signals:
    void buttonPressed();

private:
    Ui::Li_GUI *ui;
};
#endif // LI_GUI_H

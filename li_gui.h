#ifndef LI_GUI_H
#define LI_GUI_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QThread>

class workThread : public QObject {
    Q_OBJECT

public slots:
    void algorithm(std::string path) {
        // run_algorithm.sh with argument "path"
        qDebug() << "successfully ran";
    }

signals:
    void run();
};

namespace Ui { class Li_GUI; }

class Li_GUI : public QMainWindow
{
    Q_OBJECT

public:
    QThread ourThread;
    Li_GUI(QWidget *parent = nullptr);
    ~Li_GUI();

private slots:
    void on_runButton_clicked();

signals:

private:
    Ui::Li_GUI *ui;
    void readPath();
};
#endif // LI_GUI_H

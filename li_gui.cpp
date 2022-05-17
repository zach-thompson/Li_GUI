#include "li_gui.h"
#include "./ui_li_gui.h"

Li_GUI::Li_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Li_GUI)
{
    ui->setupUi(this);

    // 1. Signal object, 2. reference to function that designates signal, slot object, 4. reference to function that designates slot

    workThread *work = new workThread();
    work->moveToThread(&runThread);

    QObject::connect(this, &Li_GUI::gotPath, this, &Li_GUI::getPath);
    QObject::connect(this, &Li_GUI::gotSavePath, this, &Li_GUI::getSavePath);
    QObject::connect(this, &Li_GUI::runPressed, work, &workThread::algorithm);
    //QObject::connect(ui->runButton, &QAbstractButton::clicked, work, &workThread::algorithm);

    runThread.start();
}

Li_GUI::~Li_GUI()
{
    delete ui;
}

// monitors the "Browse" button that allows user to select a local file, returns file path
void Li_GUI::on_browseButton_clicked()
{
    QString qPath = QFileDialog::getOpenFileName();
    qDebug() << qPath;
    ui->lineEdit->setText(qPath);
    emit gotPath(qPath);
}

// returns selected file path
QString Li_GUI::getPath(QString Path){
    this->qPath = Path;
    return qPath;
}

// monitors the "Browse" button that allows user to select save location
void Li_GUI::on_browseButton_2_clicked()
{
    QString savePath = QFileDialog::getOpenFileName();
    qDebug() << savePath;
    ui->lineEdit_2->setText(savePath);
    emit gotSavePath(savePath);
}

// returns selected save location
QString Li_GUI::getSavePath(QString Path){
    this->savePath = Path;
    return savePath;
}

// monitors the "Run" button that initiates the program, emits run signal
void Li_GUI::on_runButton_clicked()
{
    emit runPressed(qPath, savePath);
}




#include "li_gui.h"
#include "./ui_li_gui.h"

Li_GUI::Li_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Li_GUI)
{
    ui->setupUi(this);

    // 1. Signal object, 2. reference to function that designates signal, slot object, 4. reference to function that designates slot
    QObject::connect(this, &Li_GUI::buttonPressed, this, &Li_GUI::readPath);
    // QObject::connect(this, &workThread::run, this, &workThread::algorithm);
}

    workThread *work = new workThread();
    work->moveToThread(&runThread);
    QObject::connect(ui->runButton, &QAbstractButton::clicked, work, &workThread::algorithm);
    Qobject::connect(work, &workThread::ranAlgorithm, this, &li_GUI::didItRun);

    runThread.start();

Li_GUI::~Li_GUI()
{
    delete ui;
}

// monitors the "Run" button that initiates the program
void Li_GUI::on_runButton_clicked()
{
    ui->is_running->setText("Running");

    emit buttonPressed();
}

// this reads in the file path provided by the user once "Run" is pressed
std::string Li_GUI::readPath()
{
    qDebug() << "checking for valid path";
    QFile inputFile(":/input");
    inputFile.open(QIODevice::ReadOnly);
    // add error checking for invalid path
    QTextStream in(&inputFile);
    QString qPath = in.readAll();
    std::string path = qPath.toStdString();

    qDebug() << qPrintable(qPath); // prints path to debugger
    return path;
    inputFile.close();
}

void Li_GUI::didItWork(QString &ran) {
    ui->is_running->setText(ran);
    runThread.exit();
}

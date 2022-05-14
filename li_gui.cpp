#include "li_gui.h"
#include "./ui_li_gui.h"

Li_GUI::Li_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Li_GUI)
{
    ui->setupUi(this);

    // 1. Signal object, 2. reference to function that designates signal, slot object, 4. reference to function that designates slot
    QObject::connect(this, &workThread::run, this, &workThread::algorithm);
}

    workThread *work = new workThread();
    work->moveToThread(&ourThread);
    // change

    QObject::connect(ui->runButton, &QAbstractButton::clicked, work, &workThread::algorithm);

Li_GUI::~Li_GUI()
{
    delete ui;
}


void Li_GUI::on_runButton_clicked()
{
    ui->is_running->setText("Running");

    emit run();
}

void Li_GUI::readPath()
{
    QFile inputFile(":/input");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString path = in.readAll();
    inputFile.close();
}

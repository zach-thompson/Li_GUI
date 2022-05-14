#include "li_gui.h"
#include "./ui_li_gui.h"

Li_GUI::Li_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Li_GUI)
{
    ui->setupUi(this);
}

Li_GUI::~Li_GUI()
{
    delete ui;
}


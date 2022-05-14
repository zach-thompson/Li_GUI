#include "li_gui.h"

#include <QApplication>

int main(int argc, char *argv[]) // Running on program thread
{
    QApplication a(argc, argv); // Creating GUI thread
    Li_GUI window;
    window.show();
    return a.exec(); // Running GUI thread
}

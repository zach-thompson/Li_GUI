#ifndef LI_GUI_H
#define LI_GUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Li_GUI; }
QT_END_NAMESPACE

class Li_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Li_GUI(QWidget *parent = nullptr);
    ~Li_GUI();

private:
    Ui::Li_GUI *ui;
};
#endif // LI_GUI_H

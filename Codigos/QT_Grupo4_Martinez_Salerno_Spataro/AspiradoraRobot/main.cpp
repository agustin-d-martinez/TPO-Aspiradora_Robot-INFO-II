#include "pantallaprincipal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PantallaPrincipal w;
    QMainWindow wnd;

    w.move(650,300);

    w.show();


    return a.exec();
}

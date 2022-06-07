#include "chiffoumi.h"
#include "dialogconnection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialogconnection *C= new Dialogconnection();
    chifoumi w;
    C->exec();
    if(C->connecter)
    {
        w.show();
        return a.exec();
    }
    return 0;
}

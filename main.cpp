#include <QtGui/QApplication>
#include "chatplusserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatPlusServer w;
    w.show();

    return a.exec();
}

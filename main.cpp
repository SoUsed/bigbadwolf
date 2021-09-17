#include "bigbadwolf.h"
#include <QApplication>

QString strPath;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    strPath = QApplication::applicationDirPath()+QString("/resources/");

    BigBadWolf w;
    w.show();

    return a.exec();
}

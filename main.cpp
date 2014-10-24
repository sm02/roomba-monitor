#include <QCoreApplication>

#include "test.h"
#include <QTimer>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test t;
    Log l;

    QTimer::singleShot(0, &t, SLOT(test1()));
    QTimer::singleShot(500, &t, SLOT(test2()));

    return a.exec();
}

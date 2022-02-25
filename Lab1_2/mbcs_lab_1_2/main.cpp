#include "hackerapp.h"
#include <QDir>
#include <QMessageBox>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HackerApp w;
    w.show();
    return a.exec();
}

#include "mydir.h"

MyDir::MyDir()
{
    dir = new QDir;
    secrecy = INVALID;
}

MyDir::MyDir(QString path)
{
    dir = new QDir(path);
    secrecy = NO_SECRET;
}

MyDir::~MyDir()
{

}

void MyDir::set_secrecy(unsigned int s)
{
    secrecy = s;
}

unsigned int MyDir::get_secrecy()
{
    return secrecy;
}

QString MyDir::get_dirname()
{
    QStringList sl = dir->path().split("/");
    return sl.last();
}

QStringList MyDir::get_filenames()
{
    return dir->entryList(QDir::Files | QDir::NoDotAndDotDot);
}

QString MyDir::get_full_path()
{
    return dir->path();
}

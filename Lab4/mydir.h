#ifndef MYDIR_H
#define MYDIR_H

#include <QDir>

enum MyRights
{
    INVALID = 0,
    NO_SECRET = 1,
    SECRET = 2,
    TOP_SECRET = 3
};

class MyDir
{
public:
    MyDir();
    MyDir(QString);
    ~MyDir();

    void set_secrecy(unsigned int);
    unsigned int get_secrecy();
    QString get_dirname();
    QStringList get_filenames();
    QString get_full_path();

private:
    QDir *dir;
    unsigned int secrecy;

};

#endif // MYDIR_H

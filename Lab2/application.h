#ifndef APPLICATION_H
#define APPLICATION_H

#include <settingspanel.h>
#include <adminpanel.h>
#include <userpanel.h>

#include <QApplication>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int argc, char *argv[]);
    ~Application();
private:
    QSqlDatabase db;
    SettingsPanel *sp;

private slots:
    void set_db_name(QString);
    void create_db(QString);
    void check_db_status();
    void get_request(send_request);
    void get_check(check_data);

    void get_grant(QString uf, QString ut, QStringList p);
    void get_remove(QString u, QStringList p);
    void get_create(QString un, QStringList p);

signals:
    void send_data(recieved_data);

};

#endif // APPLICATION_H

#include "application.h"

Application::Application(int argc, char *argv[])
    : QApplication(argc,argv)
{
    sp = new SettingsPanel();
    sp->show();
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("")

    connect(sp,SIGNAL(send_set_db_path(QString)),
            this, SLOT(set_db_name(QString)));
    connect(sp,SIGNAL(send_create_db(QString)),
            this, SLOT(create_db(QString)));
    connect(sp,SIGNAL(send_check_db()),
            this, SLOT(check_db_status()));

    connect(sp->ap,SIGNAL(send_data(send_request)),
            this, SLOT(get_request(send_request)));

    connect(this, SIGNAL(send_data(recieved_data)),
            sp->ap, SLOT(setup(recieved_data)));

    connect(sp->up,SIGNAL(send_check(check_data)),
            this, SLOT(get_check(check_data)));

    connect(sp->tgp,SIGNAL(grant(QString,QString,QStringList)),
            this, SLOT(get_grant(QString,QString,QStringList)));
    connect(sp->tgp,SIGNAL(remove(QString,QStringList)),
            this, SLOT(get_remove(QString,QStringList)));
    connect(sp->tgp,SIGNAL(create(QString,QStringList)),
            this, SLOT(get_create(QString,QStringList)));

}

Application::~Application()
{
    delete sp;
}

void Application::set_db_name(QString path)
{
    db.setDatabaseName(path);
    qDebug() << "set_db_name: " << path;
}

void Application::create_db(QString path)
{
    db.setDatabaseName(path);
    if (!db.open())
    {
        qDebug() << "ошибка";
        sp->set_status(2);
        //тут обработаем ошибку открытия
    }
    else
    {
        qDebug() << "не ошибка";

        QSqlQuery query("SHOW TABLES LIKE 'SECURITY'");
        if (query.size() != 1)
        {
            query.exec("CREATE TABLE 'SECURITY' ( 'id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,	'name'	TEXT);");
        }
        sp->set_status(1);

    }
    qDebug() << "create_db: " << path;
}

void Application::check_db_status()
{
    if (db.open())
    {
        QSqlQuery query("SHOW TABLES LIKE 'SECURITY'");
        if (query.size() != 1)
        {
            query.exec("CREATE TABLE 'SECURITY' ( 'id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,	'name'	TEXT);");
        }
        sp->set_status(1);
        qDebug() << "check_db_status: " << "1";
    }
    else
    {
        sp->set_status(2);
        qDebug() << "check_db_status: " << "2";
    }
}

void Application::get_request(send_request sr)
{
    recieved_data rd;
    QSqlQuery query;
    switch (sr.command_type)
    {
    case CHECK:
        qDebug() << "CHECK recieved";
        query.exec("SELECT name FROM SECURITY");
        while (query.next())
        {
            QString username = query.value(0).toString();
            rd.users.push_back(username);
        }

        query.exec("select name from pragma_table_info('SECURITY');");
        query.next();
        query.next();
        while (query.next())
        {
            QString permission_name= query.value(0).toString();
            rd.permissions.push_back(permission_name);
        }
        for (qsizetype i = 0; i < rd.permissions.size(); i++)
        {
            if (sr.data[0] == "") sr.data[0] = rd.users[0];
            QString request = "SELECT " + rd.permissions[i] + " FROM SECURITY WHERE name = '" + sr.data[0] + "';";
            query.exec(request);
            if (query.next())
            {
                QString perm = query.value(0).toString();
                rd.user_permissions.push_back(rd.permissions[i]+" : "+perm);
            }
            else
            {
                qDebug() << "Ошибка получения данных о ячейке";
                return;
            }
        }
        emit(send_data(rd));
        sp->up->load_users(rd.users);
        sp->tgp->setup(rd.users,rd.permissions);
        break;
    case ADD_PERMISSION:
        {
        qDebug() << "ADD_PERMISSION recieved |" << sr.data[0];
        QString request = "ALTER TABLE 'SECURITY' ADD COLUMN '" + sr.data[0] + "' TEXT DEFAULT '-';";
        query.exec(request);

        break;
        }

    case ADD_USER:
        {
        qDebug() << "ADD_USER recieved";
        QString request = "INSERT INTO 'SECURITY' (name) VALUES ('" + sr.data[0] + "');";
        query.exec(request);

        break;
        }
    case DELETE_USER:
        {
        qDebug() << "DELETE_USER recieved";
        QString request = "DELETE FROM SECURITY WHERE name = '" + sr.data[0] + "';";
        query.exec(request);

        break;
        }
    case CHANGE_USER_NAME:
        {
        qDebug() << "CHANGE_USER_NAME recieved | old : " << sr.data[0] << " | new : " << sr.data[1];
        QString request = "UPDATE 'SECURITY' SET name = '"+sr.data[1] + "' WHERE name = '" + sr.data[0] + "';";
        query.exec(request);
        break;
        }
    case CHANGE_PERMISSION:
        {
        qDebug() << "CHANGE_PERMISSION recieved";
        QString request = "UPDATE SECURITY SET " + sr.data[1] + " = '"+sr.data[2] + "' WHERE name = '" + sr.data[0] + "';";
        query.exec(request);
        break;
        }
    default:
        break;
    }
}

void Application::get_check(check_data cd)
{

    QStringList perm;

    QSqlQuery query;
    query.exec("select name from pragma_table_info('SECURITY');");
    query.next();
    query.next();
    while (query.next())
    {
        QString permission_name= query.value(0).toString();
        perm.push_back(permission_name);
    }
    QStringList inp_split = cd.input.split("");
    for (qsizetype i = 0; i < inp_split.size(); i++)
    {
        bool flag = true;
        for (qsizetype j = 0; j < perm.size(); j++)
        {
            if (inp_split[i] == perm[j])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            inp_split.removeAt(i);
            i--;
        }
    }


    for (qsizetype i = 0; i < inp_split.size(); i++)
    {
        QString request = "SELECT " + inp_split[i] + " FROM SECURITY WHERE name = '" + cd.name + "';";
        query.exec(request);
        if (query.next())
        {
            QString tmp = query.value(0).toString();
            if (tmp == "-")
            {
                inp_split.removeAt(i);
                i--;
            }
        }
    }

    QString res = "";
    for (qsizetype i = 0; i < inp_split.size(); i++)
    {
        res += inp_split[i];
    }


    sp->up->check_result(res);
}


void Application::get_grant(QString uf, QString ut, QStringList p)
{
    QSqlQuery query;
    QString request;
    for (qsizetype i = 0; i < p.size(); i++)
    {
        request = "SELECT " + p[i] + " FROM SECURITY WHERE name = '" + uf + "';";
        query.exec(request);
        if (query.next())
        {
            QString perm = query.value(0).toString();
            request = "UPDATE SECURITY SET " + p[i] + " = '" + perm + "' WHERE name = '" + ut + "';";
            query.exec(request);
        }
        else
        {
            qDebug() << "Ошибка получения данных о ячейке";
            return;
        }
    }
    sp->ap->update();
}

void Application::get_remove(QString u, QStringList p)
{
    QSqlQuery query;
    QString request = "UPDATE SECURITY SET";
    for (qsizetype i = 0; i < p.size(); i++)
    {
        if (i != 0) request += ",";
        request += " " + p[i] + " = '-'";
    }
    request += " WHERE name = '" + u + "';";
    query.exec(request);
    sp->ap->update();
}

void Application::get_create(QString un, QStringList p)
{
    QSqlQuery query;
    QStringList perm,perm_to_add;
    QString request;

    query.exec("select name from pragma_table_info('SECURITY');");
    query.next();
    query.next();
    while (query.next())
    {
        QString permission_name = query.value(0).toString();
        perm.push_back(permission_name);
    }
    for (qsizetype i = 0; i < p.size(); i++)
    {
        bool flag = true;
        for (qsizetype j = 0; j < perm.size(); j++)
        {
            if (p[i] == perm[j])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            perm_to_add.push_back(p[i]);
        }
    }

    for (qsizetype i = 0; i < perm_to_add.size(); i++)
    {
        request = "ALTER TABLE 'SECURITY' ADD COLUMN '" + perm_to_add[i] + "' TEXT DEFAULT '-';";
        query.exec(request);
    }





    request =  "INSERT INTO SECURITY (name";
    for (qsizetype i = 0; i < p.size(); i++)
    {
        request += ", " + p[i];
    }
    request += ") VALUES ('" + un + "'";
    for (qsizetype i = 0; i < p.size(); i++)
    {
        request += ", '+'";
    }
    request += ");";
    query.exec(request);
    qDebug() << request;
    sp->ap->update();
}

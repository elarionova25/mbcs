#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QMainWindow>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class AdminPanel; }
QT_END_NAMESPACE

struct recieved_data
{
    QStringList permissions;
    QStringList users;
    QStringList user_permissions;
};

enum REQUEST_TYPE
{
    CHECK = 0, //одна строка - имя текущего пользователя
    ADD_PERMISSION = 1,//одна строка - название разрешения которое надо добавить
    ADD_USER = 2,//одна строка - имя пользователя которого нужно добавить
    DELETE_USER = 3,//одна строка - имя пользователя которого нужно удалить
    CHANGE_USER_NAME = 4,//две строки - [0]-старое имя [1]-новое имя
    CHANGE_PERMISSION = 5,//три строки - [0]-имя пользователя [1]-имя разрешения [2]-состояние разрешения которое надо установить
};


struct send_request
{
    unsigned int command_type;
    QStringList data;
};

class AdminPanel : public QMainWindow
{
    Q_OBJECT

public:
    AdminPanel(QWidget *parent = nullptr);
    ~AdminPanel();
    void update();

private slots:
    void on_pushButton_add_permission_clicked();

    void on_pushButton_add_user_clicked();

    void on_radioButton_yes_clicked();

    void on_radioButton_no_clicked();

    void on_listWidget_permissions_user_currentTextChanged(const QString &currentText);

    void on_pushButton_delete_user_clicked();

    void on_pushButton_edit_user_name_clicked();

    void on_listWidget_permissions_user_clicked(const QModelIndex &index);



    void on_listWidget_users_clicked(const QModelIndex &index);

public slots:
    void setup(recieved_data);

signals:
    void send_data(send_request);
private:
    Ui::AdminPanel *ui;

};
#endif // ADMINPANEL_H

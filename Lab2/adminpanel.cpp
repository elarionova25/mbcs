#include "adminpanel.h"
#include "ui_adminpanel.h"

AdminPanel::AdminPanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::update()
{
    send_request sr;
    sr.command_type = CHECK;
    sr.data.push_back(ui->lineEdit_user_name->text());
    emit (send_data(sr));
}

void AdminPanel::setup(recieved_data rd)
{
    int tmp;

    tmp = ui->listWidget_permissions_global->currentRow();
    ui->listWidget_permissions_global->clear();
    ui->listWidget_permissions_global->addItems(rd.permissions);
    if(ui->listWidget_permissions_global->count() > tmp)
    {
        ui->listWidget_permissions_global->setCurrentRow(tmp);
    }

    tmp = ui->listWidget_users->currentRow();
    ui->listWidget_users->clear();
    ui->listWidget_users->addItems(rd.users);
    if(ui->listWidget_users->count() > tmp)
    {
        ui->listWidget_users->setCurrentRow(tmp);
    }

    if(ui->listWidget_users->currentRow()>=0)
    {
        ui->lineEdit_user_name->setText(ui->listWidget_users->currentItem()->text());
    }
    else
    {
        ui->lineEdit_user_name->setText(ui->listWidget_users->item(0)->text());
    }


    tmp = ui->listWidget_permissions_user->currentRow();
    ui->listWidget_permissions_user->clear();
    ui->listWidget_permissions_user->addItems(rd.user_permissions);
    ui->listWidget_permissions_user->setCurrentRow(tmp<0?0:tmp);

    if (ui->listWidget_permissions_user->count() == 0)
    {
        ui->radioButton_yes->setChecked(false);
        ui->radioButton_no->setChecked(false);
    }
    else
    {

        QString tmp_string = ui->listWidget_permissions_user->currentItem()->text();
        QStringList sl = tmp_string.split(" : ");
        if (sl[1] == "+")
        {
            ui->radioButton_yes->setChecked(true);
            ui->radioButton_no->setChecked(false);
        }
        else
        {
            ui->radioButton_yes->setChecked(false);
            ui->radioButton_no->setChecked(true);
        }
    }
}


void AdminPanel::on_pushButton_add_permission_clicked()
{
    QString permission_name = QInputDialog::getText(this,
                                                    "Добавление разрешения",
                                                    "Имя:",
                                                    QLineEdit::Normal);
    qDebug() << "Считано имя разрешения: " << permission_name;
    if (permission_name != "")
    {

        send_request sr;
        sr.command_type = ADD_PERMISSION;
        sr.data.push_back(permission_name);
        emit (send_data(sr));

        update();
    }
}

void AdminPanel::on_listWidget_users_clicked(const QModelIndex &index)
{
    ui->lineEdit_user_name->setText(ui->listWidget_users->currentItem()->text());
    update();
}
void AdminPanel::on_pushButton_add_user_clicked()
{
    QString user_name = QInputDialog::getText(this,
                                              "Добавление пользователя",
                                              "Имя:",
                                              QLineEdit::Normal);
    qDebug() << "Считано имя пользователя: " << user_name;
    if (user_name != "")
    {

        //добавляем строку в базу
        send_request sr;
        sr.command_type = ADD_USER;
        sr.data.push_back(user_name);
        emit(send_data(sr));

        update();
    }
}

void AdminPanel::on_pushButton_edit_user_name_clicked()
{
    QString user_name_old = ui->lineEdit_user_name->text();
    QString user_name_new = QInputDialog::getText(this,
                                              "Изменение имени пользователя",
                                              "Имя:",
                                              QLineEdit::Normal);
    qDebug() << "Считано новое имя пользователя: " << user_name_new;
    if (user_name_new != "")
    {

        //добавляем строку в базу
        send_request sr;
        sr.command_type = CHANGE_USER_NAME;
        sr.data.push_back(user_name_old);
        sr.data.push_back(user_name_new);
        emit(send_data(sr));
        ui->lineEdit_user_name->setText(user_name_new);
        update();
    }

}

void AdminPanel::on_pushButton_delete_user_clicked()
{
    QString user_name = ui->lineEdit_user_name->text();

    send_request sr;
    sr.command_type = DELETE_USER;
    sr.data .push_back(user_name);
    emit(send_data(sr));
    ui->lineEdit_user_name->setText("");

    update();
}

void AdminPanel::on_radioButton_yes_clicked()
{
    ui->radioButton_no->setChecked(false);
    qDebug() << "rB Yes clicked";

    //меняем ячейку в базе
    send_request sr;
    sr.command_type = CHANGE_PERMISSION;
    sr.data.push_back(ui->lineEdit_user_name->text());
    QStringList sl = ui->listWidget_permissions_user->currentItem()->text().split(" : ");
    sr.data.push_back(sl[0]);
    sr.data.push_back("+");
    emit(send_data(sr));

    update();
}


void AdminPanel::on_radioButton_no_clicked()
{
    ui->radioButton_yes->setChecked(false);
    qDebug() << "rB No clicked";

    //меняем ячейку в базе
    send_request sr;
    sr.command_type = CHANGE_PERMISSION;
    sr.data.push_back(ui->lineEdit_user_name->text());
    QStringList sl = ui->listWidget_permissions_user->currentItem()->text().split(" : ");
    sr.data.push_back(sl[0]);
    sr.data.push_back("-");
    emit(send_data(sr));

    update();
}

void AdminPanel::on_listWidget_permissions_user_currentTextChanged(const QString &currentText)
{
    //update();
}
void AdminPanel::on_listWidget_permissions_user_clicked(const QModelIndex &index)
{
    update();
}


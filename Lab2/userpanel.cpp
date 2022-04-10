#include "userpanel.h"
#include "ui_userpanel.h"

UserPanel::UserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPanel)
{
    ui->setupUi(this);
}

UserPanel::~UserPanel()
{
    delete ui;
}

void UserPanel::on_pushButton_check_clicked()
{
    if (ui->listWidget_users->currentRow()==-1)
    {
        qDebug() << "Не выбран пользователь";
    }
    else
    {
        check_data cd;
        cd.input = ui->lineEdit_input->text();
        cd.name = ui->listWidget_users->currentItem()->text();
        emit(send_check(cd));
    }
}

void UserPanel::check_result(QString s)
{
    ui->lineEdit_output->setText(s);
}

void UserPanel::on_listWidget_users_currentRowChanged(int currentRow)
{
    ui->lineEdit_output->setText("");
}

void UserPanel::load_users(QStringList ul)
{
    ui->listWidget_users->clear();
    ui->listWidget_users->addItems(ul);
}

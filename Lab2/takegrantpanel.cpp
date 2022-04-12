#include "takegrantpanel.h"
#include "ui_takegrantpanel.h"

TakeGrantPanel::TakeGrantPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TakeGrantPanel)
{
    ui->setupUi(this);
}

TakeGrantPanel::~TakeGrantPanel()
{
    delete ui;
}

void TakeGrantPanel::setup(QStringList users, QStringList permissions)
{
    ui->listWidget_grant_users_from->clear();
    ui->listWidget_grant_users_to->clear();
    ui->listWidget_remove_users->clear();
    ui->listWidget_grant_permissions->clear();
    ui->listWidget_remove_permissions->clear();
    ui->lineEdit_create_permissions->setText("");
    ui->lineEdit_create_username->setText("");

    ui->listWidget_grant_users_from->addItems(users);
    ui->listWidget_grant_users_to->addItems(users);
    ui->listWidget_remove_users->addItems(users);
    ui->listWidget_grant_permissions->addItems(permissions);
    ui->listWidget_remove_permissions->addItems(permissions);
}

void TakeGrantPanel::on_pushButton_Grant_clicked()
{
    if (ui->listWidget_grant_users_from->currentRow() == -1 ||
            ui->listWidget_grant_users_to->currentRow() == -1)
    {
        return;
    }
    QString user_from = ui->listWidget_grant_users_from->currentItem()->text(),
            user_to = ui->listWidget_grant_users_to->currentItem()->text();
    QStringList permissions;
    for (qsizetype i = 0; i < ui->listWidget_grant_permissions->selectedItems().size(); i++)
    {
        permissions.push_back(ui->listWidget_grant_permissions->selectedItems()[i]->text());
    }
    emit(grant(user_from,user_to,permissions));
}

void TakeGrantPanel::on_pushButton_Remove_clicked()
{
    if (ui->listWidget_remove_users->currentRow() == -1)
    {
        return;
    }
    QString user = ui->listWidget_remove_users->currentItem()->text();
    QStringList permissions;
    for (qsizetype i = 0; i < ui->listWidget_remove_permissions->selectedItems().size(); i++)
    {
        permissions.push_back(ui->listWidget_remove_permissions->selectedItems()[i]->text());
    }
    emit(remove(user,permissions));
}

void TakeGrantPanel::on_pushButton_Create_clicked()
{
    if (ui->lineEdit_create_permissions->text() == "" || ui->lineEdit_create_username->text() == "")
    {
        return;
    }
    QString username = ui->lineEdit_create_username->text();
    QStringList permissions = ui->lineEdit_create_permissions->text().split(";");
    emit(create(username,permissions));
}

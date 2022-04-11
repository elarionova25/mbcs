#include "settingspanel.h"
#include "ui_settingspanel.h"

SettingsPanel::SettingsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsPanel)
{
    ui->setupUi(this);
    set_status(0);
    ap = new AdminPanel();
    up = new UserPanel();
    tgp = new TakeGrantPanel();
}

SettingsPanel::~SettingsPanel()
{
    delete ui;
}

void SettingsPanel::set_status(unsigned short status)
{
    QString status_text;
    QColor status_color;
    switch (status)
    {
    case UNKNOWN:
        status_text = "UNKNOWN";
        status_color = Qt::gray;
        break;
    case SUCCESS:
        status_text = "SUCCESS";
        status_color = Qt::green;
        break;
    case ERROR:
        status_text = "ERROR";
        status_color = Qt::red;
        break;
    default:
        status_text = "UNKNOWN";
        status_color = Qt::gray;
        break;
    }
    ui->lineEdit_db_status->setText(status_text);
    QPalette tmp = ui->lineEdit_db_status->palette();
    tmp.setColor(QPalette::Text, status_color);
    ui->lineEdit_db_status->setPalette(tmp);
}



void SettingsPanel::on_pushButton_select_path_clicked()
{
    QString db_path = QFileDialog::getOpenFileName(this,"Open DB file",".","*.sqlite");
    if (db_path!="")
    {
        ui->lineEdit_db_path->setText(db_path);
        emit(send_set_db_path(db_path));
    }

}

void SettingsPanel::on_pushButton_create_db_clicked()
{
    QString db_path = QFileDialog::getSaveFileName(this,"Create DB file",".",".sqlite");
    if (db_path!="")
    {
        ui->lineEdit_db_path->setText(db_path);
        emit(send_create_db(db_path));
    }
}

void SettingsPanel::on_pushButton_check_db_clicked()
{
    emit(send_check_db());
}

void SettingsPanel::on_pushButton_admin_panel_clicked()
{
    ap->show();
    ap->update();
}

void SettingsPanel::on_pushButton_user_panel_clicked()
{
    up->show();
    ap->update();
}


void SettingsPanel::on_pushButton_takegrant_panel_clicked()
{
    tgp->show();
    ap->update();
}

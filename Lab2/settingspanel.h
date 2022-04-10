#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <adminpanel.h>
#include <userpanel.h>

#include <QWidget>
#include <QFileDialog>

enum DB_STATUS
{
    UNKNOWN = 0,
    SUCCESS = 1,
    ERROR = 2,
};

namespace Ui {
class SettingsPanel;
}

class SettingsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPanel(QWidget *parent = nullptr);
    ~SettingsPanel();
    void set_status(unsigned short);

    AdminPanel *ap;
    UserPanel *up;



private slots:
    void on_pushButton_select_path_clicked();

    void on_pushButton_create_db_clicked();

    void on_pushButton_admin_panel_clicked();

    void on_pushButton_user_panel_clicked();

    void on_pushButton_check_db_clicked();

private:
    Ui::SettingsPanel *ui;

signals:
    void send_set_db_path(QString);
    void send_create_db(QString);
    void send_check_db();

};

#endif // SETTINGSPANEL_H

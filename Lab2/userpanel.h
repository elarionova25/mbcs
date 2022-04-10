#ifndef USERPANEL_H
#define USERPANEL_H

#include <QWidget>

struct check_data
{
    QString name;
    QString input;
};

namespace Ui {
class UserPanel;
}

class UserPanel : public QWidget
{
    Q_OBJECT

public:
    explicit UserPanel(QWidget *parent = nullptr);
    ~UserPanel();

private slots:
    void on_pushButton_check_clicked();

    void on_listWidget_users_currentRowChanged(int currentRow);

public:
    void check_result(QString);
    void load_users(QStringList);

signals:
    void send_check(check_data);

private:
    Ui::UserPanel *ui;
};

#endif // USERPANEL_H

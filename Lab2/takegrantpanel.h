#ifndef TAKEGRANTPANEL_H
#define TAKEGRANTPANEL_H

#include <QWidget>

namespace Ui {
class TakeGrantPanel;
}

class TakeGrantPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TakeGrantPanel(QWidget *parent = nullptr);
    ~TakeGrantPanel();
    void setup(QStringList users, QStringList permissions);

private slots:
    void on_pushButton_Grant_clicked();

    void on_pushButton_Remove_clicked();

    void on_pushButton_Create_clicked();

private:
    Ui::TakeGrantPanel *ui;

signals:
    void grant(QString user_from, QString user_to, QStringList permissions);
    void remove(QString user, QStringList permissions);
    void create(QString username, QStringList permissions);
};

#endif // TAKEGRANTPANEL_H

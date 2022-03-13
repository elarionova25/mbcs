#ifndef HACKERAPP_H
#define HACKERAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class HackerApp; }
QT_END_NAMESPACE

class HackerApp : public QMainWindow
{
    Q_OBJECT

public:
    HackerApp(QWidget *parent = nullptr);
    ~HackerApp();
    QByteArray buffer;

private slots:
    void on_check_btn_clicked();

private:
    Ui::HackerApp *ui;
};
#endif // HACKERAPP_H

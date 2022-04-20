#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <mydir.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_choose_workdir_clicked();

    void on_radioButton_TS_clicked();

    void on_radioButton_S_clicked();

    void on_radioButton_N_clicked();

    void on_listWidget_dirs_currentTextChanged(const QString &currentText);

    void on_listWidget_dirs_from_currentTextChanged(const QString &currentText);

    void on_pushButton_update_clicked();

    void on_pushButton_copy_clicked();

private:
    Ui::MainWindow *ui;

    void change_secrecy(unsigned int);

    QVector <MyDir> data;
    QString ws_path;
};
#endif // MAINWINDOW_H

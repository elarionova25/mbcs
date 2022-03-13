#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_save_btn_clicked()
{
//     ui->input_text->setText("save");

     QString data = ui->input_text->text();

    if (!QDir("private").exists())
     {
         QDir().mkdir("private");
     }

    QFile private_file("private/data.txt");

    private_file.open(QIODevice::WriteOnly|QIODevice::Text);

    if (private_file.isOpen())
    {
        private_file.write(data.toStdString().c_str());
        private_file.close();
        QMessageBox::information(nullptr, "success", "data is saved");
        ui->input_text->setText("");
    }
    else
    {
        QMessageBox::warning(nullptr, "error", "file open error");
    }
    return;
}


void MainWindow::on_load_btn_clicked()
{
// ui->input_text->setText("load");
    QByteArray data;

    QFile private_file("private/data.txt");
    private_file.open(QIODevice::ReadOnly);

    if (private_file.isOpen())
    {
       data = private_file.readAll();
       private_file.close();
    }
    else
    {
       QMessageBox::warning(nullptr, "error", "private file open error");
       return;
    }

    if (!QDir("public").exists())
    {
        QDir().mkdir("public");
    }

    QFile public_file("public/data.txt");

    public_file.open(QIODevice::WriteOnly);

    if (public_file.isOpen())
    {
        public_file.write(data);
        public_file.close();
        QMessageBox::information(nullptr, "succsess", "data is loaded");
    }
    else
    {
        QMessageBox::warning(nullptr, "error", "public file open error");
    }
    return;
}




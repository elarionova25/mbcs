#include "hackerapp.h"
#include "ui_hackerapp.h"
#include <QDir>
#include <QMessageBox>


HackerApp::HackerApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HackerApp)
{
    ui->setupUi(this);
}

HackerApp::~HackerApp()
{
    delete ui;
}


void HackerApp::on_check_btn_clicked()
{
   QByteArray data;

   if (!QDir("public").exists())
    {
         QMessageBox::information(nullptr, "Error", "no public dir");
         return;
    }

    QFile public_file("public/data.txt");

    if (!public_file.exists())
    {
        QMessageBox::information(nullptr, "Error", "no public file");
        return;
    }

    public_file.open(QIODevice::ReadOnly);

    data = public_file.readAll();

    if(this->buffer==data)
    {
        QMessageBox::information(nullptr, "Info", "no new data");
    }

    else
    {
        this->buffer = data;

        QFile hacker_file("hacker/data.txt");

        if (!QDir("hacker").exists())
         {
              QMessageBox::information(nullptr, "Error", "no public dir");
              return;
         }

        hacker_file.open(QIODevice::WriteOnly|QIODevice::Text);
        hacker_file.write(this->buffer.toStdString().c_str());
        hacker_file.close();
        QMessageBox::information(nullptr, "success", "data is saved");
        ui->buffer->setText(data);
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_choose_workdir_clicked()
{
    QString tmp = QFileDialog::getExistingDirectory(nullptr,"Выбор рабочей папки");
    if (tmp != "")
    {
        ws_path = tmp;
        ui->lineEdit_ws_path->setText(tmp);
    }

}

void MainWindow::on_radioButton_TS_clicked()
{
    change_secrecy(TOP_SECRET);
}

void MainWindow::on_radioButton_S_clicked()
{
    change_secrecy(SECRET);
}

void MainWindow::on_radioButton_N_clicked()
{
    change_secrecy(NO_SECRET);
}

void MainWindow::change_secrecy(unsigned int s)
{
    QString dirname = ui->listWidget_dirs->currentItem()->text();
    for (qsizetype i = 0; i < data.length(); i++)
    {
        if(data[i].get_dirname() == dirname)
        {
            data[i].set_secrecy(s);
            return;
        }
    }
    //и тут тоже можно сделать окно с ошибкой
}
void MainWindow::on_listWidget_dirs_currentTextChanged(const QString &currentText)
{
    for (qsizetype i = 0; i < data.length(); i++)
    {
        if(data[i].get_dirname() == currentText)
        {
            switch (data[i].get_secrecy())
            {
            case NO_SECRET:
                ui->radioButton_N->setChecked(true);
                break;
            case SECRET:
                ui->radioButton_S->setChecked(true);
                break;
            case TOP_SECRET:
                ui->radioButton_TS->setChecked(true);
                break;
            default:
                break;

            }
            return;
        }
    }
    //тут можно сделать окно с ошибкой
}

void MainWindow::on_listWidget_dirs_from_currentTextChanged(const QString &currentText)
{
    for (qsizetype i = 0; i < data.length(); i++)
    {
        if(data[i].get_dirname() == currentText)
        {
            //тут сделаем вывод списка файлов в выбранной папке
            ui->listWidget_files->clear();
            ui->listWidget_files->addItems(data[i].get_filenames());
            return;
        }
    }
    //тоже можно сделать окно с ошибкой
}

void MainWindow::on_pushButton_update_clicked()
{
    data.clear();
    QDir dir(ws_path);
    QStringList tmp = dir.entryList(QDir::Dirs| QDir::NoDotAndDotDot);
    for (qsizetype i = 0; i < tmp.length(); i++)
    {
        data.push_back(MyDir(ws_path+"/"+tmp[i]));
        qDebug() << data.last().get_dirname();
    }
    ui->listWidget_dirs->clear();
    ui->listWidget_dirs_from->clear();
    ui->listWidget_dirs_to->clear();

    ui->listWidget_dirs->addItems(tmp);
    ui->listWidget_dirs_from->addItems(tmp);
    ui->listWidget_dirs_to->addItems(tmp);
    if (ui->listWidget_dirs_from->count()>0)
    {
        ui->listWidget_dirs_from->setCurrentRow(0);
    }
    if (ui->listWidget_dirs_to->count()>0)
    {
        ui->listWidget_dirs_to->setCurrentRow(0);
    }
    if (ui->listWidget_dirs->count()>0)
    {
        ui->listWidget_dirs->setCurrentRow(0);
    }
}

void MainWindow::on_pushButton_copy_clicked()
{
    if (ui->listWidget_dirs_from->currentRow() == -1 | ui->listWidget_dirs_to->currentRow() == -1 | ui->listWidget_files->currentRow() == -1)
    {
        QMessageBox::warning(nullptr,"Ошибка","Выберите исходную и целевую папки и файл для копирования");
        return;
    }
    QString from_name = ui->listWidget_dirs_from->currentItem()->text(),
            to_name = ui->listWidget_dirs_to->currentItem()->text(),
            file_name = ui->listWidget_files->currentItem()->text(),
            from_path,to_path;
    MyDir   *from_dir = nullptr,
            *to_dir = nullptr;
    if (from_name == to_name)
    {
        QMessageBox::warning(nullptr,"Ошибка","Выберите разные исходную и целевую папки");
        return;
    }
    for (qsizetype i = 0; i < data.length(); i++)
    {
        if(data[i].get_dirname() == from_name)
        {
            from_dir = &data[i];
        }
        if (data[i].get_dirname() == to_name)
        {
            to_dir = &data[i];
        }
    }
    if (from_dir == nullptr | to_dir == nullptr)
    {
        QMessageBox::warning(nullptr,"Ошибка","Неизвестная ошибка №1");
        return;
    }

    if (from_dir->get_secrecy()>to_dir->get_secrecy())
    {
        QMessageBox::warning(nullptr,"Ошибка","Вы не можете копировать файлы из более конфеденциальной папки в менее конфеденциальную");
        return;
    }

    from_path = from_dir->get_full_path()+"/"+file_name;
    to_path = to_dir->get_full_path()+"/"+file_name;

    while(QFile::exists(to_path))
    {
        QString tmp = QInputDialog::getText(nullptr,"Ошибка","Файл с таким именем уже существует введите новое название (не должно быть пустым)");
        if (tmp=="") continue;
        else to_path = to_dir->get_full_path()+"/"+tmp;
    }

    if (!QFile::copy(from_path,to_path))
    {
        QMessageBox::warning(nullptr,"Ошибка","Неизвестная ошибка №2");
        return;
    }

}

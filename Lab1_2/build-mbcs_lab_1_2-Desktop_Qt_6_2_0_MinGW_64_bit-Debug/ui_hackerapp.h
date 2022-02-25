/********************************************************************************
** Form generated from reading UI file 'hackerapp.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HACKERAPP_H
#define UI_HACKERAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HackerApp
{
public:
    QWidget *centralwidget;
    QPushButton *check_btn;
    QLineEdit *buffer;

    void setupUi(QMainWindow *HackerApp)
    {
        if (HackerApp->objectName().isEmpty())
            HackerApp->setObjectName(QString::fromUtf8("HackerApp"));
        HackerApp->resize(800, 600);
        centralwidget = new QWidget(HackerApp);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        check_btn = new QPushButton(centralwidget);
        check_btn->setObjectName(QString::fromUtf8("check_btn"));
        check_btn->setGeometry(QRect(60, 320, 161, 61));
        buffer = new QLineEdit(centralwidget);
        buffer->setObjectName(QString::fromUtf8("buffer"));
        buffer->setGeometry(QRect(60, 120, 651, 151));
        buffer->setReadOnly(true);
        HackerApp->setCentralWidget(centralwidget);

        retranslateUi(HackerApp);

        QMetaObject::connectSlotsByName(HackerApp);
    } // setupUi

    void retranslateUi(QMainWindow *HackerApp)
    {
        HackerApp->setWindowTitle(QCoreApplication::translate("HackerApp", "HackerApp", nullptr));
        check_btn->setText(QCoreApplication::translate("HackerApp", "Check", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HackerApp: public Ui_HackerApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HACKERAPP_H

/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QLineEdit *UsernameLineEdit;
    QLabel *UsernameLabel;
    QLabel *PasswordLabel;
    QLineEdit *PasswordLineEdit;
    QPushButton *pushButton;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(639, 387);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        UsernameLineEdit = new QLineEdit(centralwidget);
        UsernameLineEdit->setObjectName(QString::fromUtf8("UsernameLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, UsernameLineEdit);

        UsernameLabel = new QLabel(centralwidget);
        UsernameLabel->setObjectName(QString::fromUtf8("UsernameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, UsernameLabel);

        PasswordLabel = new QLabel(centralwidget);
        PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, PasswordLabel);

        PasswordLineEdit = new QLineEdit(centralwidget);
        PasswordLineEdit->setObjectName(QString::fromUtf8("PasswordLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, PasswordLineEdit);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout->setWidget(2, QFormLayout::FieldRole, pushButton);

        LoginWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "LoginWindow", nullptr));
        UsernameLabel->setText(QCoreApplication::translate("LoginWindow", "UserName:", nullptr));
        PasswordLabel->setText(QCoreApplication::translate("LoginWindow", "PassWord:", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginWindow", "Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include "userauthentication.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <event.h>

LoginWindow::LoginWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow() { delete ui; }
void LoginWindow::keyPressEvent(QKeyEvent* event)
{
    QKeyEvent* key = static_cast<QKeyEvent*>(event);
    if ((key->key() == Qt::Key_Enter) || key->key() == Qt::Key_Return) {
        if (ui->UsernameLineEdit->text() == NULL && ui->PasswordLineEdit->text() != NULL) {
            msgBox->setText("Enter Your Name");
            msgBox->exec();
        }
        if (ui->PasswordLineEdit->text() == NULL && ui->UsernameLineEdit->text() != NULL) {
            msgBox->setText("Enter Your Passwd");
            msgBox->exec();
        }
        if (ui->PasswordLineEdit->text() == NULL && ui->UsernameLineEdit->text() == NULL) {
            msgBox->setText("Enter Your Name And Password And Press Enter");
            msgBox->exec();
        }
        if (ui->PasswordLineEdit->text() != NULL && ui->UsernameLineEdit->text() != NULL) {
            pid_t child_pid;
            if (login(ui->UsernameLineEdit->text().toStdString(), ui->PasswordLineEdit->text().toStdString(), &child_pid)) {
                msgBox->setText("Success");
                msgBox->exec();
            } else {
                msgBox->setText("Failed");
                msgBox->exec();
            }
        }
    }
}

void LoginWindow::on_pushButton_clicked()
{
    if (ui->UsernameLineEdit->text() == NULL && ui->PasswordLineEdit->text() != NULL) {
        msgBox->setText("Enter Your Name");
        msgBox->exec();
    }
    if (ui->PasswordLineEdit->text() == NULL && ui->UsernameLineEdit->text() != NULL) {
        msgBox->setText("Enter Your Passwd");
        msgBox->exec();
    }
    if (ui->PasswordLineEdit->text() == NULL && ui->UsernameLineEdit->text() == NULL) {
        msgBox->setText("Enter Your Name And Password And Press Enter");
        msgBox->exec();
    }
    if (ui->PasswordLineEdit->text() != NULL && ui->UsernameLineEdit->text() != NULL) {
        // function to login start everything and wait it for it
    }
}

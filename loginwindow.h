#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

private:
    QMessageBox *msgBox = new QMessageBox();
    Ui::LoginWindow *ui;

protected:
    void keyPressEvent(QKeyEvent *);
};
#endif // LOGINWINDOW_H

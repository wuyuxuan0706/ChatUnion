#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"
#include "register.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private:
    void init();

private slots:
    void on_login_btn_clicked();

    void on_label_linkActivated(const QString &link);

private:
    Ui::login *ui;
    MainWindow *homewindow=nullptr;
    Register *register_window=nullptr;
};

#endif // LOGIN_H

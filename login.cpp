#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    init();

    homewindow = new MainWindow;
    homewindow->hide();

    register_window = new Register;
    register_window->hide();
}

login::~login()
{
    delete ui;
}

void login::on_login_btn_clicked()
{
    homewindow->show();
    this->close();
}

void login::on_label_linkActivated(const QString &link)
{
    register_window->show();
}

void login::init() {

};

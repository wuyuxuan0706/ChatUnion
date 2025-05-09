#include "register.h"
#include "ui_register.h"
#include "global.h"
#include "httpmgr.h"

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->pass_line->setEchoMode(QLineEdit::Password);
    ui->conpass_line->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);
    connect(httpmgr::GetInstances().get(), &httpmgr::sig_reg_mod_finish,
            this, &Register::slot_reg_mod_finish);

    InitHttpHandlers();
}

Register::~Register()
{
    delete ui;
}

void Register::on_cancel_line_clicked()
{
    this->close();
}


void Register::on_send_btn_clicked()
{
    auto email = ui->email_line->text();
    //wuyuxuanxxx0706@gmail.com
    static QRegularExpression regex(R"(^([a-zA-Z0-9._%+-]+)@([a-zA-Z0-9-]+)(\.([a-zA-Z]{2,}))+$)");
    bool match = regex.match(email).hasMatch();
    if (match) {
        //send vertification code
        QJsonObject json_obj;
        json_obj["email"] = email;
        httpmgr::GetInstances()->PostHttpReq(QUrl("http://localhost:8080/get_varifycode"), json_obj,
                                             ReqId::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);
    } else {
        ShowTip(tr("Wrong email address"), false);
    }

}

void Register::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        ShowTip(tr("ONLINE REQUEST WRONG"), false);
        return;
    }

    //序列化和反序列化
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDoc.isNull()){
        ShowTip(tr("json解析失败"), false);
        return;
    }
    if (!jsonDoc.isObject()){
        ShowTip(tr("json解析失败"), false);
        return;
    }

    //
    _handlers[id](jsonDoc.object());
    return;
}

void Register::InitHttpHandlers()
{
    //注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS){
            ShowTip(tr("参数错误"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        ShowTip(tr("验证码已发送，请注意查收！"), true);
        qDebug() << "email is" << email;
    });
}

void Register::ShowTip(QString str, bool b_ok)
{
    if(b_ok) {
        ui->err_tip->setProperty("state", "normal");
    } else {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}


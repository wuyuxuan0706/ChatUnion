#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_cancel_line_clicked();

    void on_send_btn_clicked();

    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);

private:
    void InitHttpHandlers();
    void ShowTip(QString str, bool b_ok);
    Ui::Register *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>>_handlers;
};

#endif // REGISTER_H

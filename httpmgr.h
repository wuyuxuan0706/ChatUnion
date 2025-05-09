#ifndef HTTPMGR_H
#define HTTPMGR_H

#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

//CRTP?
class httpmgr:public QObject, public Singleton<httpmgr>,
                public std::enable_shared_from_this<httpmgr>
{
    Q_OBJECT
public:
    ~httpmgr();
private:
    friend class Singleton<httpmgr>;
    httpmgr();
    QNetworkAccessManager _manager;
public:
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H

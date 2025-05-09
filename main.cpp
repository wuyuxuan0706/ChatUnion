#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ChatUnion_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    QFile qss(":/stylesheet/stylesheet.css");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("Open succeed");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    } else {
        qDebug("Open failed");
    }
    login login;
    login.show();

    return a.exec();
}

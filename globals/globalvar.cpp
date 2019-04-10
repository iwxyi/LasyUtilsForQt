
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QDateTime>
#include <QTime>
#include "settings.h"
#include "usettings.h"
#include "frisoutil.h"
#include "lexicon.h"
#include "runtimeinfo.h"

QString APPLICATION_NAME = "写作天下";
QString VERSION_NUMBER = "v0.6.4";

USettings* us;
RuntimeInfo* rt;
FrisoUtil* friso_AI;
Lexicons* lexicon_AI;

bool deb(QVariant str, QString name)
{
    qDebug() << "-------【" << name << "】-------";
    qDebug() << str.toString() << endl;
    return true;
}

bool deb(QVariant str)
{
    qDebug() << "------------------------";
    qDebug() << str.toString() << endl;
    return true;
}

void Log(QVariant str)
{
    if (us != nullptr && us->is_debug)
        deb(str);
}

QString Path(QString str)
{
    if (str.endsWith("/"))
        return rt->DATA_PATH + str;
    else
        return rt->DATA_PATH + str + "/";
}

void initGlobal()
{
    rt = new RuntimeInfo();
    us = new USettings(rt->DATA_PATH+"settings.ini");
    friso_AI = new FrisoUtil();
    lexicon_AI = new Lexicons(rt->DATA_PATH + "lexicon/");
}

void Log(QVariant str, QString title)
{
    Q_UNUSED(str);
    Q_UNUSED(title);
    //deb(str, title);
}

void deleteGlobal()
{
    friso_AI->Destructor();

    delete us;
    //delete frisoAI;
}

/**
 * 毫秒级获取时间戳
 * @return 时间戳
 */
qint64 getTimestamp()
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}

/**
 * 全局变量
 */

#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <QCoreApplication>
#include "settings.h"
#include "usettings.h"
#include "frisoutil.h"
#include "lexicon.h"
#include "runtimeinfo.h"

// ==== 应用 ====
extern QString APPLICATION_NAME;
extern QString VERSION_NUMBER;

extern RuntimeInfo* rt;
extern USettings* us;
extern FrisoUtil* friso_AI;
extern Lexicons* lexicon_AI;

extern bool deb(QVariant str, QString name);
extern bool deb(QVariant str);
extern void Log(QVariant str);
extern void Log(QVariant str, QString title);
extern QString Path(QString str);
extern qint64 getTimestamp();

void initGlobal();
void deleteGlobal();

#endif // GLOBALVAR_H

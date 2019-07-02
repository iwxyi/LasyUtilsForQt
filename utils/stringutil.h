/**
 * 文本操作工具
 */

#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <QString>
#include <QStringList>
#include <QColor>
#include <QDebug>

#define XML_SPLIT "5YaZ5L2c5aSp5LiL"

QStringList getStrMids(QString text, QString l, QString r); // 取中间文本数组
QString getStrMid(QString text, QString l, QString r); // 取中间文本2

QString fnEncode(QString text); // 可使用的文件名编码
QString fnDecode(QString text); // 文件名解码

bool canRegExp(QString str, QString pat); // 能否正则匹配

QString getXml(QString str, QString pat);
QStringList getXmls(QString str, QString pat);
QString makeXml(QString str, QString pat);
QString makeXml(int i, QString pat);
QString makeXml(qint64 i, QString pat);

QString ArabToCN(int num);

#endif // STRINGUTIL_H

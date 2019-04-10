/**
 * 全局运行状态类
 */

#ifndef RUNTIMEINFO_H
#define RUNTIMEINFO_H

#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QObject>
#include "fileutil.h"
#include "defines.h"


class RuntimeInfo
{
public:
    RuntimeInfo();

    void checkApplicationUpdateFile();
    void initPath();
    void initIntegral();
    void initEggs();

    bool promptCreateNovel(QWidget* w);
    void setLineGuideWidget(QWidget* w);
    void finishLineGuide();

public:
    // ==== 路径 ====
    QString APP_PATH;   // 运行路径
    QString DATA_PATH;  // 数据总路径
    QString NOVEL_PATH; // 小说总路径
    QString THEME_PATH; // 主题路径
    QString IMAGE_PATH; // 主题-图片路径
    QString STYLE_PATH; // 主题-界面路径
    QString DOWNLOAD_PATH; // 下载路径
    QString DOMAIN_PATH; // 域名路径
    QString SERVER_PATH; // 服务路径

    // ==== 运行 ====
    qint64 startup_timestamp; // 启动时间
    bool is_initing; // 初始化中
    int has_new_version;

    // ==== 统计 ====
    int USER_WORD; // 用户字数
    int USER_TIME; // 用户时间
    int USER_ADDI; // 额外积分
    int USER_LEVEL; // 用户等级

    // ==== 彩蛋 ====
    int NO_NOVEL_PROMPT_COUNT;  // 提示创建书籍次数，3次则提示
    bool is_line_guide;
    int line_guide_case;
    QWidget* guide_widget;
};


#endif // RUNTIMEINFO_H

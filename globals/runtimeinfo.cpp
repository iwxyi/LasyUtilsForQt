#include "runtimeinfo.h"


RuntimeInfo::RuntimeInfo()
{
    startup_timestamp = 0;
    is_initing = true;
    has_new_version = 0;

    initPath();
    initIntegral();
    initEggs();
}

void RuntimeInfo::checkApplicationUpdateFile()
{
    QString zip_path = APP_PATH + "/download/update.zip";
}

void RuntimeInfo::initPath()
{
#if defined(Q_OS_WIN32)
    APP_PATH = QCoreApplication::applicationDirPath();
#elif defined(Q_OS_ANDROID)
    APP_PATH = "/data/data/com.iwxyi.writerfly/";
#endif
    if (!APP_PATH.endsWith("/")) APP_PATH += "/";
    DATA_PATH = APP_PATH+"data/";
    NOVEL_PATH = DATA_PATH + "novels/";
    THEME_PATH = DATA_PATH + "themes/";
    IMAGE_PATH = DATA_PATH+"image/";
    STYLE_PATH = DATA_PATH+"style/";
    DOWNLOAD_PATH = APP_PATH + "download/";
    DOMAIN_PATH = "http://writerfly.cn";
    SERVER_PATH = DOMAIN_PATH + "/writerfly/";

    ensureDirExist(DATA_PATH);
    ensureDirExist(NOVEL_PATH);

    checkApplicationUpdateFile();
}

void RuntimeInfo::initIntegral()
{

}

void RuntimeInfo::initEggs()
{
    NO_NOVEL_PROMPT_COUNT = 0;
    is_line_guide = false;
    line_guide_case = LINE_GUIDE_NONE;
    guide_widget = nullptr;
}

/**
 * 趣味提示
 * @param w
 * @return 是否需要线条支持
 */
bool RuntimeInfo::promptCreateNovel(QWidget *w)
{
    ++NO_NOVEL_PROMPT_COUNT;
    if (NO_NOVEL_PROMPT_COUNT == 3)
    {
        QMessageBox::information(w, QObject::tr("没!有!作!品!"), QObject::tr("你这汉子，好不晓事！\n最后再说一遍，要先创建新书！"));
        line_guide_case = LINE_GUIDE_CREATE_BOOK;
        return true;
    }
    else if (NO_NOVEL_PROMPT_COUNT > 3)
        ;
    else
        QMessageBox::information(w, QObject::tr("没有作品"), QObject::tr("请点击上方的“创建新书”来建立一个作品"));
    return false;
}

void RuntimeInfo::setLineGuideWidget(QWidget *w)
{
    return ; // 此处有重绘 bug

    is_line_guide = true;
    guide_widget = w;
}

void RuntimeInfo::finishLineGuide()
{
    is_line_guide = false;
    line_guide_case = LINE_GUIDE_NONE;
    guide_widget = nullptr;
}

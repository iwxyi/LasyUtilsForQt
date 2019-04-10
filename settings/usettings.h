#ifndef USETTINGS_H
#define USETTINGS_H

#include "settings.h"
#include <QColor>

/**
 * 程序总设置类
 */
class USettings : public Settings
{
public:

    USettings(QString filePath);

    void init();
    void loadFromFile();
    QString getOpacityColor(QColor color, int transparent);

public:

    bool is_debug;                   // 调试模式

    /* ==== 界面 ==== */
    int     mainwin_titlebar_height; // 标题栏高度
    QString mainwin_bg_picture;      // 背景图片，如果是文件夹则随机
    QColor  mainwin_bg_color;        // 窗口背景颜色，用于在图片背后，-1为无


    bool    mainwin_sidebar_hide;    // 侧边栏是否折叠
    int     mainwin_sidebar_width;   // 侧边栏的固定宽度，为0则自适应
    QColor  mainwin_sidebar_color;   // 侧边栏的颜色，为了和背景颜色适配，要调整透明度
    int     mainwin_sidebar_spacing; // 目录章节间的间隔

    QColor  global_font_color;       // 全局字体颜色（除了编辑框外的所有字体颜色）
    QColor  primary_color;           // 强调色

    QColor  editor_bg_color;         // 编辑框的背景颜色
    int     editor_font_size;        // 编辑框的字体大小
    QColor  editor_font_color;       // 编辑框的字体颜色
    QColor  editor_bg_selection;     // 选中的背景颜色
    QColor  editor_font_selection;   // 选中的字体颜色
    QColor  editor_bg_line;          // 光标所在行背景颜色
    int     editor_cursor_width;     // 光标宽度

    bool    settings_in_mainwin;     // 在主窗口打开设置（背景模糊效果）

    /* ==== 交互 ==== */
    bool    one_click;               // 单击操作：单击打开章节分组+双击重命名、双击打开章节分组+菜单重命名
    int     tab_maxnum;              // 打开的 tab widget 个数
    bool    open_chapter_animation;  // 打开章节的动画
    bool    open_recent;             // 启动时自动打开最后一次的章节
    bool    scroll_cursor_fixed;     // 全文光标固定
    int     scroll_bottom_blank;     // 底部空白（滚动超过最后一行）
    bool    scroll_bottom_fixed;     // 末尾固定位置
    bool    scroll_suspension;       // 悬浮滚动
    bool    cursor_animation;        // 光标移动动画
    bool    input_animation;         // 输入文字动画

    /* ==== 数据 ==== */
    bool    save_power;              // 强力保存：每写一个字就进行保存
    int     save_interval;           // 自动保存的时间间隔(单位分钟)，仅在 powerSave 关闭时有效
    int     editor_recorder_max;     // 撤销的最大次次数

    /* ==== 功能 ==== */
    int     indent_blank;            // 段首空格
    int     indent_line;             // 段落空行
    bool    smart_quotes;            // 双引号变成智能引号
    bool    change_apos;             // 单击引号实现智能引号效果(针对双引号按键修复)
    bool    smart_space;             // 智能空格
    bool    smart_enter;             // 智能回车
    bool    smart_backspace;         // 智能删除
    bool    tab_complete;            // tab完成
    bool    tab_skip;                // tab跳过
    bool    auto_punc;               // 自动标点
    bool    punc_cover;              // 标点覆盖
    bool    space_quotes;            // 空格引号
    bool    pair_match;              // 括号匹配
    bool    pair_jump;               // 括号跳转
    bool    homonym_cover;           // 同音词覆盖
    QString homonym_cover_blanklist; // 同音词覆盖黑名单

    bool    para_after_quote;        // 多段后引号
    bool    para_auto_split;         // 回车自动分段
    int     para_max_length;         // 自动分段的上限
    bool    typeset_split;           // 排版时长段落自动分段
    bool    typeset_blank;           // 中文和字母数字间增加空格
    bool    typeset_paste;           // 多段粘贴排版
    bool    typeset_english;         // 排版时首字母大写、标点后空格

    /* ==== 词典 ==== */
    bool    lexicon_synonym;         // 同义词词典
    bool    lexicon_related;         // 相关词词典
    bool    lexicon_sentence;        // 句子词典
    bool    lexicon_random;          // 随机取名
    int     completer_input_delay;   // 输入后提示延时
    int     completer_cursor_delay;  // 移动后提示延时
    int     completer_maxnum;        // 自动提示最大显示项数
    bool    completer_random;        // 词典乱序显示
    bool    insert_sentence;         // 句子是否直接插入而不复制


    /* ==== 常量 ==== */



};


#endif // USETTINGS_H

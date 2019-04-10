#include "usettings.h"

USettings::USettings(QString filePath) : Settings(filePath)
{
    init();
}

void USettings::init()
{
    is_debug = true;

    loadFromFile();
}

void USettings::loadFromFile()
{
    /* ---- 界面 ---- */
    mainwin_titlebar_height = getInt("us/mainwin_titlebar_height", 40);
    mainwin_bg_picture      = getStr("us/mainwin_bg_picture", "");
    mainwin_bg_color        = getColor("us/mainwin_bg_color", QColor(0xFF, 0xFF, 0xFF));

    mainwin_sidebar_hide    = getBool("us/mainwin_sidebar_hide", false);
    mainwin_sidebar_width   = getInt("us/mainwin_sidebar_width", 200);
    mainwin_sidebar_color   = getColor("us/mainwin_sidebar_color", QColor(0xEE, 0xEE, 0xEE, 0x88));
    mainwin_sidebar_spacing = getInt("us/mainwin_sidebar_spacing", 2);

    primary_color           = getColor("us/primary_color", QColor(0x64, 0x95, 0xED));

    editor_bg_color         = getColor("us/editor_bg_color", QColor(0x00, 0x00, 0x00, 0x00));
    editor_font_size        = getInt("us/editor_font_size", 15);
    editor_font_color       = getColor("us/editor_font_color", QColor(0x00, 0x00, 0x00, 0xFF));
    editor_bg_selection     = getColor("us/editor_bg_selection", QColor(0x59, 0x5b, 0x5d));
    editor_font_selection   = getColor("us/editor_font_selection", QColor(0xFF, 0xFF, 0xFF));
    editor_bg_line          = getColor("us/editor_bg_line", QColor(0x88, 0x88, 0x88, 20));
    editor_cursor_width     = getInt("us/editor_cursor_width", 2);

    settings_in_mainwin     = getBool("us/settings_in_mainwin", true);

    /* ---- 数据 ---- */
    save_power              = getBool("us/save_power", true);
    save_interval           = getInt("us/save_interval", 0);
    editor_recorder_max     = getInt("us/editor_recorder_max", 100);

    /* ---- 交互 ---- */
    one_click               = getBool("us/one_click", true);
    tab_maxnum              = getInt("us/tab_maxnum", 20);
    open_chapter_animation  = getBool("us/open_chapter_animation", true);
    open_recent             = getBool("us/open_recent", true);
    scroll_cursor_fixed     = getBool("us/scroll_cursor_fixed", false);
    scroll_bottom_blank     = getInt("us/scroll_bottom_blank", 2);
    scroll_bottom_fixed     = getBool("us/scroll_bottom_fixed", true);
    cursor_animation        = getBool("us/cursor_animation", true);
    input_animation         = getBool("us/input_animation", true);

    /* ---- 功能 ---- */
    indent_blank            = getInt("us/indent_blank", 2);
    indent_line             = getInt("us/indent_line", 1);

    smart_quotes            = getBool("us/smart_quotes", true);
    change_apos             = getBool("us/change_apos", true);
    smart_space             = getBool("us/smart_space", true);
    smart_enter             = getBool("us/smart_enter", true);
    smart_backspace         = getBool("us/smart_backspace", true);
    tab_complete            = getBool("us/tab_complete", true);
    tab_skip                = getBool("us/tab_skip", true);
    auto_punc               = getBool("us/auto_punc", true);
    punc_cover              = getBool("us/punc_cover", true);
    space_quotes            = getBool("us/space_quotes", true);
    pair_match              = getBool("us/pair_match", true);
    pair_jump               = getBool("us/pair_jump", true);
    homonym_cover           = getBool("us/homonym_cover", true);
    homonym_cover_blanklist = getStr("us/homonym_cover_blanklist", "");
    para_after_quote        = getBool("us/para_after_quote", true);
    para_auto_split         = getBool("us/para_auto_split", false);
    para_max_length         = getInt("us/para_max_length", 300);

    typeset_split           = getBool("us/typeset_split", false);
    typeset_blank           = getBool("us/typeset_blank", true);
    typeset_paste           = getBool("us/typeset_paste", true);
    typeset_english         = getBool("us/typeset_english", false);

    /* ---- 词典 ---- */
    lexicon_synonym         = getBool("us/lexicon_synonym", true);
    lexicon_related         = getBool("us/lexicon_related", true);
    lexicon_sentence        = getBool("us/lexicon_sentence", true);
    lexicon_random          = getBool("us/lexicon_random", true);
    completer_input_delay   = getInt("us/completer_input_delay", 1);
    completer_cursor_delay  = getInt("us/completer_cursor_delay", 1000);
    completer_maxnum        = getInt("us/completer_maxnum", 7);
    completer_random        = getBool("us/completer_random", true);
    insert_sentence         = getBool("us/insert_sentence", false);

}

QString USettings::getOpacityColor(QColor color, int transparent)
{
    int r = color.red(), g = color.green(), b = color.blue();
    return QString("rgb(%1,%2,%3,%4)").arg(r).arg(g).arg(b).arg(transparent);
}



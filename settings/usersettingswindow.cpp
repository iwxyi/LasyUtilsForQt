#include "usersettingswindow.h"

UserSettingsWindow::UserSettingsWindow(QWidget* parent) : QFrame(parent)
{
    //setModal(true); // 模态窗口，必须关闭

    // 设置布局
    QHBoxLayout* hlayout = new QHBoxLayout(this);
    group_list = new QListWidget;
    item_list = new QListWidget;
    hlayout->addWidget(group_list);
    hlayout->addWidget(item_list);
    hlayout->setStretch(0, 2);
    hlayout->setStretch(1, 5);
    hlayout->setSpacing(0);
    hlayout->setMargin(0);
    group_list->setMinimumWidth(50);
    item_list->setMinimumWidth(100);
    group_list->setResizeMode(QListView::Adjust);
    item_list->setResizeMode(QListView::Adjust);
    item_list->setVerticalScrollMode(QListWidget::ScrollPerPixel);
    item_list->verticalScrollBar()->setSingleStep(10);

    this->setLayout(hlayout);

    QString widget_style = "QFrame{background: rgb(255,255,255,200); border: none;}";
    widget_style += "QLabel{background:transparent;}";
    this->setStyleSheet(widget_style);

    QString list_style = "QListWidget{background: transparent; }";
    group_list->setStyleSheet(list_style);
    item_list->setStyleSheet(list_style);

    if (isFileExist(rt->STYLE_PATH + "scrollbar.qss"))
        item_list->verticalScrollBar()->setStyleSheet(readTextFile(rt->STYLE_PATH + "scrollbar.qss"));

    initItems();
}

/**
 * 初始化所有设置项
 */
void UserSettingsWindow::initItems()
{
    /* ==== 分类 ==== */
    QStringList group_names, grounp_icons;
    group_names << tr("外观风格") << tr("特色功能") << tr("词典提示") << tr("交互操作") << tr("文章排版");
    grounp_icons << "appearance" << "feature" << "lexicon" << "interaction" << "typeset";
    QFont font("Microsoft YaHei", 15);
    for (int i = 0; i < group_names.size(); i++)
    {
        QListWidgetItem* item = new QListWidgetItem(group_list);
        //item->setTextAlignment(Qt::AlignRight);
        item->setSizeHint(QSize(80, GROUPS_HEIGHT));
        item->setText(group_names.at(i));
        item->setFont(font);

        QPixmap pixmap(":/icons/setting/" + grounp_icons.at(i));
        QIcon icon(pixmap);
        item->setIcon(icon);
    }
    connect(group_list, SIGNAL(currentRowChanged(int)), this, SLOT(slotScrollToGroup(int)));

    /* ==== 界面 ==== */
    QString update_str = "";
    if (rt->has_new_version == 1) update_str = " (新版下载中，关闭后自动更新)";
    else if (rt->has_new_version == 2) update_str = " (新版已下载，关闭后自动更新)";
    addItems("about", "写作天下 "+VERSION_NUMBER + update_str, "反馈/建议/素材/合作 之QQ交流群：：705849222", "哼哼，加群也没用，开发者忙着玩儿呢，哪来的时间更新呀？");

    addGroup("", "界面风格", "");
    addItems("mainwin_bg_picture", "窗口背景图片", "暂时只支持 png、jpg", "修改图片格式产生不同的效果：png格式图片会覆盖在背景颜色上面（如果透明的话）\njpg格式会被背景颜色（可调整透明度）覆盖\n后续可能支持gif动图背景", us->mainwin_bg_picture);
    addItems("mainwin_bg_color", "窗口背景颜色", "", "", us->mainwin_bg_color);

    //addItems("mainwin_sidebar_hide", "展开目录", "", "", us->mainwin_sidebar_hide);
    //addItems("mainwin_sidebar_width", "目录宽度", "", "", us->mainwin_sidebar_width);
    addItems("mainwin_sidebar_color", "目录背景颜色", "", "", us->mainwin_sidebar_color);

    // addItems("primary_color", "程序主色调", "", "", us->primary_color);

    // addItems("editor_bg_color", "编辑框背景颜色", "", "", us->editor_bg_color);
    addItems("editor_font_size", "编辑框字体大小", "", "", us->editor_font_size);
    addItems("editor_font_color", "编辑框字体颜色", "", "", us->editor_font_color);
    addItems("editor_bg_line", "光标所在行背景颜色", "", "", us->editor_bg_line);
    addItems("editor_font_selection", "选中的文字颜色", "", "", us->editor_font_selection);
    hideItem();
    addItems("editor_bg_selection", "选中的文字背景颜色", "", "", us->editor_bg_selection);
    hideItem();
    addItems("mainwin_sidebar_spacing", "目录章节列表间距", "", "", us->mainwin_sidebar_spacing);
    hideItem();
    addItems("editor_cursor_width", "编辑框光标宽度", "", "", us->editor_cursor_width);
    hideItem();
    addItems("mainwin_titlebar_height", "标题栏高度", "", "需要重启", us->mainwin_titlebar_height);
    hideItem();
    addItems("settings_in_mainwin", "设置界面嵌入主窗口", "在主窗口中打开设置界面，显示背景模糊效果（重启生效）", "关闭此项可实时看到界面设置的改变情况", us->settings_in_mainwin);
    hideItem();
    addSplitter();

    /* ==== 功能 ==== */
    addGroup("", "特色功能", "");
    addItems("smart_quotes", "智能引号", "使用双引号键添加标点、移动光标", "根据语境，一键添加双引号、冒号、逗号、句末标点", us->smart_quotes);
    addItems("smart_space", "智能空格", "添加逗号、句末标点、跳过标点、跳过引号", "", us->smart_space);
    addItems("smart_enter", "智能回车", "双引号内回车、自动添加标点", "", us->smart_enter);
    addItems("smart_backspace", "高级删除", "删除成对的符号、连续的标点", "", us->smart_backspace);
    addItems("auto_punc", "自动标点", "在语气词或者语言动词后面自动添加上标点符号", "根据神态和语言自动分析，若有错误可直接在后面输入正确的标点来覆盖（需要开启标点覆盖）", us->auto_punc);
    addItems("space_quotes", "空格引号", "段落结尾或者新开头按空格键添加双引号", "其实在空格后面按空格键都能触发", us->space_quotes);
    addItems("tab_complete", "Tab键补全", "使用tab键补全句子结束标点", "只有句号/问号/感叹号三种，不包含逗号\nTab键功能将会覆盖原有的制表符", us->tab_complete);
    addItems("tab_skip", "Tab键跳过", "通过Tab键跳过多个标点/空格等，建议与[Tab键补全]一起食用", "常用语境：双引号内将要结束时，一键补全句末标点并跳出双引号\n也适用于中英结合的句子强制添加标点。（其实就是更懒了呀）", us->tab_skip);
    addItems("homonym_cover", "同音词覆盖", "使用相同读音的词语来覆盖光标左边已经输入的词语", "适用于手快选词出错的情况\n当前问题：无法识别多音字\n暂时不支持黑名单、模糊音（以后必定会有）", us->homonym_cover);
    addItems("punc_cover", "标点覆盖", "新标点覆盖左边的标点", "专门用来处理自动添加的错误的标点", us->punc_cover);
    hideItem();
    addItems("pair_match", "括号匹配", "自动添加右半部分符号", "会检索整个段落自动判断是否需要补全", us->pair_match);
    hideItem();
    addItems("pair_jump", "括号跳转", "多余的右半符号变为光标右移", "避免括号匹配后重复添加括号", us->pair_jump);
    hideItem();
    addItems("para_after_quote", "多段后引号", "连续多段语言描写，每段后面都加后引号，还是仅最后一段有后引号", "仅在双引号内回车时触发。\n别问为什么有这选项，我的语文老师说的……", us->para_after_quote);
    hideItem();
    addItems("para_auto_split", "自动分段", "在长段落（超过段落阈值）的结尾换行时，自动拆分此长段落", "只针对\"。！？\"这三种标点\n一长串的语言描写不会拆开", us->para_auto_split);
    hideItem();
    addItems("para_max_length", "段落阈值", "当段落文字数（包括标点）超过阈值时，识别为长段落", "", us->para_max_length);
    hideItem();
    addSplitter();

    /* ==== 词典 ==== */
    addGroup("", "词典提示", "");
    addItems("lexicon_synonym", "同义词提示", "输入词语时自动提示同义词", "关闭后，综合搜索结果中也将不显示（下同）\n当然，[综合搜索]功能还未开发，不必在意", us->lexicon_synonym);
    addItems("lexicon_related", "相关词提示", "输入词语时自动提示相关词", "", us->lexicon_related);
    addItems("lexicon_sentence", "常用句提示", "输入词语时提示用到该词语的句子，从[-->]中进入", "选中的句子会复制到剪贴板，ctrl+V 粘贴到任意位置", us->lexicon_sentence);
    addItems("lexicon_random", "随机取名提示", "输入[取名][姓氏][人名]等，随机取名", "请问您叫王富贵吗？", us->lexicon_random);
    addItems("completer_random", "词语乱序显示", "自动提示的词语随机排序", "只在同一类型的内部随机排序\n例如，同义词和相关词不会随机混合到一起，依旧是同义词在前", us->completer_random);
    hideItem();
    addItems("completer_maxnum", "自动提示展示数量", "词句后面自动提示允许同时显示的最大行数", "", us->completer_maxnum);
    hideItem();
    addItems("completer_cursor_delay", "移动光标提示延时", "移动光标后显示词典提示框的延迟时长（毫秒）", "", us->completer_cursor_delay);
    hideItem();
    addItems("completer_input_delay", "输入文字提示延时", "输入文字后显示词典提示框的延迟时长（毫秒）", "不建议太长，可能会挡住中文输入法的输入框", us->completer_input_delay);
    hideItem();
    addItems("insert_sentence", "直接插入句子", "在选中句子后，直接插入到光标处而不是复制到剪贴板", "默认关闭，尽量避免抄袭操作", us->insert_sentence);
    hideItem();
    addSplitter();

    /* ==== 交互 ==== */
    addGroup("", "交互操作", "");
    addItems("one_click", "单击交互", "目录单击打开章节/展开分卷", "", us->one_click);
    addItems("change_apos", "修改单引号", "单击引号实现智能引号效果（将无法输入单引号）", "", us->change_apos);
    //addItems("tab_maxnum", "打开章节个数", "", "", us->tab_maxnum);
    addItems("open_recent", "启动时打开最近一章", "", "自动聚焦到上次编辑的位置", us->open_recent);
    addItems("open_chapter_animation", "打开章节动画", "点击目录打开新章的缩放效果", "偷偷告诉你，这是傻开发者的动画强迫症", us->open_chapter_animation);
    addItems("cursor_animation", "光标移动动画", "", "", us->cursor_animation);
    addItems("input_animation", "文字输入动画（试验）", "可能会出现文字颜色的bug", "后续可能支持多种动画效果", us->input_animation);
    addItems("save_power", "强力保存", "实时保存，安全稳定（尽量别关）", "别关别关别关别关别关别关别关!\n好吧……关不关随你……记得 ctrl+s 保存", us->save_power);
    hideItem();
    //addItems("save_interval", "定时保存间隔[不需要]", "单位：分钟", "", us->save_interval);
    addItems("editor_recorder_max", "撤销最大次数", "", "", us->editor_recorder_max);
    hideItem();
    addItems("scroll_cursor_fixed", "光标行固定", "编辑时光标上下位置不变，反而移动文字", "光标：我只是懒得滚", us->scroll_cursor_fixed);
    hideItem();
    addItems("scroll_bottom_fixed", "底部行固定", "在全文最后面时固定光标行位置", "得配合[底部空白]使用。可能是独有的小细节", us->scroll_bottom_fixed);
    hideItem();
    addItems("scroll_bottom_blank", "底部空白", "在编辑框底部留点空白区域，避免眼睛一直向下看", "可以自定义留白的高度\n0为关闭，1~10设置成总高度的几分之一，大于10为像素单位", us->scroll_bottom_blank);
    hideItem();
    addSplitter();

    /* ==== 排版 ==== */
    addGroup("", "文章排版", "");
    addItems("indent_blank", "段首空格", "回车缩进，段首的全角空格数量", "", us->indent_blank);
    addItems("indent_line", "段落空行", "回车时段落间增加空白行", "空行不会影响网站上发布的效果", us->indent_line);
    addItems("typeset_blank", "排版插入空格", "排版（Ctrl+T）时在中文和字母数字之间自动插入一个空格", "会在所有情况下都插入空格，若用到特殊词语请关闭此项", us->typeset_blank);
    addItems("typeset_split", "排版自动分段", "排版时将长段落（超过分段阈值）自动分成多个小段", "这段落，瞎分的，不知准确性如何，请勿过于依赖此功能", us->typeset_split);
    addItems("typeset_paste", "多段粘贴排版", "粘贴多个段落时对插入的内容进行排版（Ctrl+Z撤销排版）", "若要撤销粘贴则需要按两次 Ctrl+Z", us->typeset_paste);
    addItems("typeset_english", "英文排版", "排版时将单词首字母大写、句末增加空格等", "仅单个字母不会生效", us->typeset_english);

}

void UserSettingsWindow::addItems(QString key, QString title, QString desc, QString tip, QString val)
{
    UserSettingsItem* widget = new UserSettingsItem(key, title, desc, tip, val);
    connect(widget, SIGNAL(signalClicked(UserSettingsItem*, QString)), this, SLOT(slotItemClicked(UserSettingsItem*, QString)));
    QListWidgetItem* item = new QListWidgetItem(item_list);
    item->setSizeHint(QSize(80, widget->getHeight()));
    item_list->setItemWidget(item, widget);
}

void UserSettingsWindow::addItems(QString key, QString title, QString desc, QString tip, int val)
{
    UserSettingsItem* widget = new UserSettingsItem(key, title, desc, tip, val);
    connect(widget, SIGNAL(signalClicked(UserSettingsItem*, QString)), this, SLOT(slotItemClicked(UserSettingsItem*, QString)));
    QListWidgetItem* item = new QListWidgetItem(item_list);
    item->setSizeHint(QSize(80, widget->getHeight()));
    item_list->setItemWidget(item, widget);
}

void UserSettingsWindow::addItems(QString key, QString title, QString desc, QString tip, bool val)
{
    UserSettingsItem* widget = new UserSettingsItem(key, title, desc, tip, val);
    connect(widget, SIGNAL(signalClicked(UserSettingsItem*, QString)), this, SLOT(slotItemClicked(UserSettingsItem*, QString)));
    QListWidgetItem* item = new QListWidgetItem(item_list);
    item->setSizeHint(QSize(80, widget->getHeight()));
    item_list->setItemWidget(item, widget);
}

void UserSettingsWindow::addItems(QString key, QString title, QString desc, QString tip, QColor c)
{
    UserSettingsItem* widget = new UserSettingsItem(key, title, desc, tip, c);
    connect(widget, SIGNAL(signalClicked(UserSettingsItem*, QString)), this, SLOT(slotItemClicked(UserSettingsItem*, QString)));
    QListWidgetItem* item = new QListWidgetItem(item_list);
    item->setSizeHint(QSize(80, widget->getHeight()));
    item_list->setItemWidget(item, widget);
}

void UserSettingsWindow::addItems(QString key, QString title, QString desc, QString tip)
{
    UserSettingsItem* widget = new UserSettingsItem(key, title, desc, tip);
    connect(widget, SIGNAL(signalClicked(UserSettingsItem*, QString)), this, SLOT(slotItemClicked(UserSettingsItem*, QString)));
    QListWidgetItem* item = new QListWidgetItem(item_list);
    item->setSizeHint(QSize(80, widget->getHeight()));
    item_list->setItemWidget(item, widget);
}

void UserSettingsWindow::addGroup(QString group_key, QString title, QString desc)
{
    // 点击左边的列表切换到对应的子项
    items_indexs.append(item_list->count());

    // 显示的控件
    UserSettingsItem* widget = new UserSettingsItem(group_key, title, desc);
    QListWidgetItem* item = new QListWidgetItem(item_list);
    item->setFlags(Qt::ItemIsUserCheckable);   // Qt::ItemIsUserCheckable 不可选、变灰      Qt::ItemIsEnabled  仅不可选
    item->setSizeHint(QSize(80, 10+(widget->getHeight()>>1)));
    item_list->setItemWidget(item, widget);
}

void UserSettingsWindow::addSplitter()
{
    // 显示的分割线
    UserSettingsItem* widget = new UserSettingsItem(2);
    connect(widget, SIGNAL(signalClicked(UserSettingsItem*, QString)), this, SLOT(slotItemClicked(UserSettingsItem*, QString)));
    QListWidgetItem* item = new QListWidgetItem(item_list);
    item->setSizeHint(QSize(100, 20));
    item_list->setItemWidget(item, widget);
}

/**
 * 隐藏最后一个 item
 */
void UserSettingsWindow::hideItem()
{
    item_list->item(item_list->count()-1)->setHidden(true);
}

void UserSettingsWindow::showEvent(QShowEvent *)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    //QDialog::showEvent(e);
}

void UserSettingsWindow::closeEvent(QCloseEvent *)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();

    //QDialog::closeEvent(e);
}

void UserSettingsWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        emit signalEsc();
    }

    return QFrame::keyPressEvent(event);
}

/**
 * 滚动到某一项
 * @param x 分组索引
 */
void UserSettingsWindow::slotScrollToGroup(int x)
{
    if (x >= group_list->count()) return ;
    int index = items_indexs.at(x);
    if (index >= item_list->count()) return ;

    int vi = this->height() / ITEMS_HEIGHT; // 能看见的数量
    int index2 = index;
    while (vi-- && index2 < item_list->count())
    {
        if (item_list->item(index2)->isHidden())
            vi++;
        index2++;
    }
    if (index2 >= item_list->count())
        index2 = item_list->count()-1;
    item_list->scrollTo(item_list->model()->index(index2, 0));
    //itemsList->scrollTo(itemsList->model()->index(index, 0));
    item_list->setCurrentRow(index); // 相比上面的，这个多了选中项
}

/**
 * 项目单击事件
 * @param widget 被单击的控件，用于设置修改后的数据
 * @param key    设置项关键词
 */
void UserSettingsWindow::slotItemClicked(UserSettingsItem* item, QString key)
{
    if (key == "splitter")
    {
        int current_index = item_list->currentRow();
        int current_group = 0; // 所在的分组
        while (current_group < items_indexs.size() && current_index >= items_indexs[current_group])
            current_group++;
        int end_pos = items_indexs[current_group];
        int start_pos = --current_group < 0 ? 0 : items_indexs[current_group];
        for (int i = start_pos; i < end_pos; i++)
            item_list->setItemHidden(item_list->item(i), false);
    }
    else if (key == "mainwin_titlebar_height")
    {
        int x;
        if (!inputInt(tr("窗口标题栏高度"), tr("请输入主窗口标题栏的高度（10~100），重启生效"), us->mainwin_titlebar_height, 10, 100, x))
            return ;
        //us->mainwin_titlebar_height = x; // 重启生效
        us->setVal("us/"+key, x);
        item->setVal(x);
    }
    else if (key == "mainwin_bg_picture")
    {
        // 背景图存在，删除
        if (isFileExist(rt->IMAGE_PATH+"win_bg.jpg") || isFileExist(rt->IMAGE_PATH+"win_bg.png"))
        {
            if (QMessageBox::question(this, QObject::tr("是否删除背景图？"), QObject::tr("删除之后您可以重新设置成其他图片"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes) {
                if (isFileExist(rt->IMAGE_PATH+"win_bg.png"))
                    deleteFile(rt->IMAGE_PATH+"win_bg.png");
                else
                    deleteFile(rt->IMAGE_PATH+"win_bg.jpg");
            }
            return ;
        }

        QString recent = us->getStr("recent/file_path");
        if (recent == "" || !isFileExist(recent))
            recent = ".";
        QString path = QFileDialog::getOpenFileName(this, tr("选择背景图片"), recent, tr("Image Files(*.jpg *.png)"));
        if (path.length() == 0) return ;

        us->mainwin_bg_picture = path; // 这个path好像是带双引号的？（至少debug的时候是带有双引号的）
        item->setVal(tr("清除图片"));
        us->setVal("recent/file_path", path);

        ensureDirExist(rt->IMAGE_PATH);

        if (path.endsWith("png"))
            copyFile(path, rt->IMAGE_PATH+"win_bg.png");
        else if (path.endsWith("jpg"))
            copyFile(path, rt->IMAGE_PATH+"win_bg.jpg");
        else
            copyFile(path, rt->IMAGE_PATH+"win_bg.jpg");

        parentWidget()->update();
    }
    else if (key == "mainwin_bg_color")
    {
        QColor color = QColorDialog::getColor(us->mainwin_bg_color, this, "", QColorDialog::ShowAlphaChannel);
        if (!color.isValid()) return ;
        us->mainwin_bg_color = color;
        us->setColor("us/"+key, color);

        item->setVal(color);
        parentWidget()->update();
    }
    else if (key == "mainwin_sidebar_color")
    {
        QColor color = QColorDialog::getColor(us->mainwin_sidebar_color, this, "", QColorDialog::ShowAlphaChannel);
        if (!color.isValid()) return ;
        us->mainwin_sidebar_color = color;
        us->setColor("us/"+key, color);

        item->setVal(color);
        parentWidget()->update();
    }
    else if (key == "mainwin_sidebar_spacing")
    {
        int x;
        if (!inputInt(tr("章节间间距"), tr("请输入章节之间的间距（0~10），重启生效"), us->mainwin_sidebar_spacing, 0, 10, x))
            return ;
        us->mainwin_sidebar_spacing = x;
        us->setVal("us/"+key, x);
        item->setVal(x);
    }
    else if (key == "primary_color")
    {
        QColor color = QColorDialog::getColor(us->primary_color, this, "", QColorDialog::ShowAlphaChannel);
        if (!color.isValid()) return ;
        us->primary_color = color;
        us->setColor("us/"+key, color);

        item->setVal(color);
        this->update();
        parentWidget()->update();
    }
    else if (key == "editor_bg_color")
    {
        QColor color = QColorDialog::getColor(us->editor_bg_color, this, "", QColorDialog::ShowAlphaChannel);
        if (!color.isValid()) return ;
        us->editor_bg_color = color;
        us->setColor("us/"+key, color);

        item->setVal(color);
        parentWidget()->update();

        emit signalEditorUIChanged();
    }
    else if (key == "editor_bg_selection")
    {
        QColor color = QColorDialog::getColor(us->editor_bg_selection, this, "", QColorDialog::ShowAlphaChannel);
        if (!color.isValid()) return ;
        us->editor_bg_selection = color;
        us->setColor("us/"+key, color);

        item->setVal(color);
        parentWidget()->update();

        emit signalEditorUIChanged();
    }
    else if (key == "editor_font_size")
    {
        int x;
        if (!inputInt(tr("字体大小"), tr("请输入编辑框字体大小（1~250）"), us->editor_font_size, 1, 250, x))
            return ;

        us->editor_font_size = x;
        us->setVal("us/"+key, x);
        item->setVal(x);

        parentWidget()->update();

        emit signalEditorUIChanged();
    }
    else if (key == "editor_font_color")
    {
        QColor color = QColorDialog::getColor(us->editor_font_color, this, "", QColorDialog::ShowAlphaChannel);
        if (!color.isValid()) return ;
        us->editor_font_color = color;
        us->setColor("us/"+key, color);

        item->setVal(color);
        parentWidget()->update();

        emit signalEditorUIChanged();
    }
    else if (key == "editor_font_selection")
    {
        QColor color = QColorDialog::getColor(us->editor_font_selection, this, "", QColorDialog::ShowAlphaChannel);
        if (!color.isValid()) return ;
        us->editor_font_selection = color;
        us->setColor("us/"+key, color);

        item->setVal(color);
        parentWidget()->update();

        emit signalEditorUIChanged();
    }
    else if (key == "editor_bg_line")
    {
        QColor color = QColorDialog::getColor(us->editor_bg_line, this, "", QColorDialog::ShowAlphaChannel);
        if (!color.isValid()) return ;
        us->editor_bg_line = color;
        us->setColor("us/"+key, color);

        item->setVal(color);
        parentWidget()->update();

        emit signalEditorUIChanged();
    }
    else if (key == "editor_cursor_width")
    {
        int x;
        if (!inputInt(tr("光标宽度"), tr("请输入编辑框光标宽度（1~5）"), us->editor_cursor_width, 1, 5, x))
            return ;

        us->editor_cursor_width = x;
        us->setVal("us/"+key, x);
        item->setVal(x);

        parentWidget()->update();

        emit signalEditorUIChanged();
    }
    else if (key == "settings_in_mainwin")
    {
        bool b = us->getBool("us/settings_in_mainwin", us->settings_in_mainwin); //us->settings_in_mainwin; // 避免本次点击无效
        b = !b; // 下次重启生效
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "one_click")
    {
        bool& b = us->one_click;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "tab_maxnum")
    {
        int x;
        if (!inputInt(tr("打开数量"), tr("请输入打开章节的最大数量（1~999）"), us->tab_maxnum, 1, 999, x))
            return ;

        us->tab_maxnum = x;
        us->setVal("tab_maxnum", x);
        item->setVal(x);
    }
    else if (key == "open_chapter_animation")
    {
        bool& b = us->open_chapter_animation;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "open_recent")
    {
        bool& b = us->open_recent;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "save_power")
    {
        bool& b = us->save_power;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "save_interval")
    {
        int x;
        if (!inputInt(tr("定时保存"), tr("请输入定时保存的间隔（1~999），单位：分钟。0为关闭定时保存。"), us->save_interval,0, 999, x))
            return ;

        us->save_interval = x;
        us->setVal(QString("us/%1").arg(key), x);
        item->setVal(x);
    }
    else if (key == "editor_recorder_max")
    {
        int x;
        if (!inputInt(tr("撤销次数"), tr("请输入撤销的最大次数（10~999）"), us->editor_recorder_max, 10, 999, x))
            return ;

        us->editor_recorder_max = x;
        us->setVal(QString("us/%1").arg(key), x);
        item->setVal(x);
    }
    else if (key == "scroll_bottom_blank")
    {
        int x;
        if (!inputInt(tr("底部空白"), tr("请输入空白高度（0~9999），0为关闭，1~10设置成总高度的几分之一，大于10为像素单位"), us->scroll_bottom_blank, 0, 9999, x))
            return ;

        us->scroll_bottom_blank = x;
        us->setVal(QString("us/%1").arg(key), x);
        item->setVal(x);

        emit signalEditorBottomSettingsChanged();
    }
    else if (key == "scroll_bottom_fixed")
    {
        bool& b = us->scroll_bottom_fixed;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);

        emit signalEditorBottomSettingsChanged();
    }
    else if (key == "scroll_cursor_fixed")
    {
        bool& b = us->scroll_cursor_fixed;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);

        emit signalEditorBottomSettingsChanged();
    }
    else if (key == "cursor_animation")
    {
        bool& b = us->cursor_animation;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "input_animation")
    {
        bool& b = us->input_animation;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "indent_blank")
    {
        int x;
        if (!inputInt(tr("段首缩进"), tr("请输入段落开头的空格缩进量（0~10）"), us->indent_blank, 0, 10, x))
            return ;

        us->indent_blank = x;
        us->setVal("us/indent_blank", x);
        item->setVal(x);
    }
    else if (key == "indent_line")
    {
        int x;
        if (!inputInt(tr("段间空行"), tr("请输入两段之间的空白行数量（0~10）"), us->indent_line, 0, 10, x))
            return ;

        us->indent_line = x;
        us->setVal("us/indent_line", x);
        item->setVal(x);
    }
    else if (key == "smart_quotes")
    {
        bool& b = us->smart_quotes;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "change_apos")
    {
        bool& b = us->change_apos;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "smart_space")
    {
        bool& b = us->smart_space;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "smart_enter")
    {
        bool& b = us->smart_enter;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "smart_backspace")
    {
        bool& b = us->smart_backspace;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "auto_punc")
    {
        bool& b = us->auto_punc;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "punc_cover")
    {
        bool& b = us->punc_cover;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "space_quotes")
    {
        bool& b = us->space_quotes;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "pair_match")
    {
        bool& b = us->pair_match;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "pair_jump")
    {
        bool& b = us->pair_jump;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "tab_complete")
    {
        bool& b = us->tab_complete;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "tab_skip")
    {
        bool& b = us->tab_skip;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "homonym_cover")
    {
        bool& b = us->homonym_cover;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "para_after_quote")
    {
        bool& b = us->para_after_quote;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "para_auto_split")
    {
        bool& b = us->para_auto_split;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "para_max_length")
    {
        int x;
        if (!inputInt(tr("自动分段阈值"), tr("当段落长度超过这个次数时进行分段（100~500）"), us->para_max_length, 100, 500, x))
            return ;

        us->para_max_length = x;
        us->setVal("us/para_max_length", x);
        item->setVal(x);
    }
    else if (key == "typeset_split")
    {
        bool& b = us->typeset_split;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "typeset_blank")
    {
        bool& b = us->typeset_blank;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "typeset_paste")
    {
        bool& b = us->typeset_paste;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "typeset_english")
    {
        bool& b = us->typeset_english;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "lexicon_synonym")
    {
        bool& b = us->lexicon_synonym;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);

        if (b)
            lexicon_AI->initSynonym();
        else
            lexicon_AI->uninitAll(true, false, false, false);
    }
    else if (key == "lexicon_related")
    {
        bool& b = us->lexicon_related;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);

        if (b)
            lexicon_AI->initRelated();
        else
            lexicon_AI->uninitAll(false, true, false, false);
    }
    else if (key == "lexicon_sentence")
    {
        bool& b = us->lexicon_sentence;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);

        if (b)
            lexicon_AI->initSentence();
        else
            lexicon_AI->uninitAll(false, false, true, false);
    }
    else if (key == "lexicon_random")
    {
        bool& b = us->lexicon_random;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);

        if (b)
            lexicon_AI->initRandomName();
        else
            lexicon_AI->uninitAll(false, false, false, true);
    }
    else if (key == "completer_input_delay")
    {
        int x;
        if (!inputInt(tr("延迟时长"), tr("输入文字后出现词语提示框的延迟时长，毫秒（1~10000）"), us->completer_input_delay, 1, 10000, x))
            return ;

        us->completer_input_delay = x;
        us->setVal("us/"+key, x);
        item->setVal(x);
    }
    else if (key == "completer_cursor_delay")
    {
        int x;
        if (!inputInt(tr("延迟时长"), tr("移动光标后出现词语提示框的延迟时长，毫秒（1~10000）"), us->completer_cursor_delay, 1, 10000, x))
            return ;

        us->completer_cursor_delay = x;
        us->setVal("us/"+key, x);
        item->setVal(x);
    }
    else if (key == "completer_maxnum")
    {
        int x;
        if (!inputInt(tr("显示行数"), tr("自动提示框同时显示的最大项目数（1~10）"), us->completer_maxnum, 1, 10, x))
            return ;

        us->completer_maxnum = x;
        us->setVal("us/"+key, x);
        item->setVal(x);
        emit signalEditorUIChanged();
    }
    else if (key == "completer_random")
    {
        bool& b = us->completer_random;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    else if (key == "insert_sentence")
    {
        bool& b = us->insert_sentence;
        b = !b;
        us->setVal(QString("us/%1").arg(key), b);
        item->setVal(b);
    }
    us->sync();
}

bool UserSettingsWindow::inputInt(QString title, QString desc, int def, int min, int max, int& rst)
{
    bool ok;
    QString text = QInputDialog::getText(this, title, desc, QLineEdit::Normal, QString("%1").arg(def), &ok);
    if (!ok) return false; // 没有输入
    if (!canRegExp(text, "^\\d+$")) // 不是纯数字
    {
        QMessageBox::information(this, tr("错误"), tr("请输入纯数字"));
        return false;
    }

    int x = text.toInt();
    if ((min != max) && (x < min || x > max)) // 超过范围
    {
        QMessageBox::information(this, tr("错误"), tr("请输入 %1~%2 之间的数字").arg(min).arg(max));
        return false;
    }

    rst = x;
    return true;
}

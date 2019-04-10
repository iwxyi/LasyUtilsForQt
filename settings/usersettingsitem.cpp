#include "usersettingsitem.h"

/**
 * 添加字符串形式的设置项
 * @param key   设置项关键词
 * @param title 设置项标题
 * @param desc  设置项描述
 * @param tip   设置项提示（鼠标悬浮）
 * @param val   设置项字符串值
 */
UserSettingsItem::UserSettingsItem(QString key, QString title, QString desc, QString tip, QString val)
	: key(key)
{
    QHBoxLayout* hlayout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;

    QLabel* lb_title = new QLabel(title);
    QLabel* lb_desc = new QLabel(desc);
    lb_val = new QLabel(val);

    lb_desc->setStyleSheet("color: rgb(50,50,50)");
    item_height = lb_title->fontMetrics().height() << 2;

    vlayout->addWidget(lb_title);
    if (desc != "")
    {
        vlayout->addWidget(lb_desc);
    }

    hlayout->addLayout(vlayout);
    hlayout->addWidget(lb_val);
    lb_val->setAlignment(Qt::AlignRight);

    if (tip != "")
    {
        this->setToolTip(tip);
    }

    this->setLayout(hlayout);


}

/**
 * 添加整数形式的设置项
 * @param key   设置项关键词
 * @param title 设置项标题
 * @param desc  设置项描述
 * @param tip   设置项提示（鼠标悬浮）
 * @param val   设置项整型值
 */
UserSettingsItem::UserSettingsItem(QString key, QString title, QString desc, QString tip, int val)
	: key(key)
{
    QHBoxLayout* hlayout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;

    QLabel* lb_title = new QLabel(title);
    QLabel* lb_desc = new QLabel(desc);
    nb_val = new NumberLabel(this);
    nb_val->setAlignment(Qt::AlignRight);
    nb_val->setShowNum(val);

    lb_desc->setStyleSheet("color: rgb(50,50,50)");
    item_height = lb_title->fontMetrics().height() << 2;

    vlayout->addWidget(lb_title);
    if (desc != "")
    {
        vlayout->addWidget(lb_desc);
    }
    hlayout->addLayout(vlayout);
    hlayout->addWidget(nb_val);

    if (tip != "")
    {
        this->setToolTip(tip);
    }

    this->setLayout(hlayout);


}

/**
 * 添加布尔型的设置项
 * @param key   设置项关键词
 * @param title 设置项标题
 * @param desc  设置项描述
 * @param tip   设置项提示（鼠标悬浮）
 * @param val   设置项布尔值
 */
UserSettingsItem::UserSettingsItem(QString key, QString title, QString desc, QString tip, bool val)
	: key(key)
{
    QHBoxLayout* hlayout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;

    QLabel* lb_title = new QLabel(title);
    QLabel* lb_desc = new QLabel(desc);
    as = new AniSwitch(val);
    as->setMaximumWidth(SWITCH_WIDTH);
    as->setMinimumWidth(SWITCH_WIDTH);

    lb_desc->setStyleSheet("color: rgb(50,50,50)");
    item_height = lb_title->fontMetrics().height() << 2;

    vlayout->addWidget(lb_title);
    if (desc != "")
    {
        vlayout->addWidget(lb_desc);
    }
    hlayout->addLayout(vlayout);
    hlayout->addWidget(as);

    if (tip != "")
    {
        this->setToolTip(tip);
    }

    this->setLayout(hlayout);

}

/**
 * 添加颜色形式的设置项
 * @param key   设置项关键词
 * @param title 设置项标题
 * @param desc  设置项描述
 * @param tip   设置项提示（鼠标悬浮）
 * @param val   设置项颜色值
 */
UserSettingsItem::UserSettingsItem(QString key, QString title, QString desc, QString tip, QColor c)
	: key(key)
{
    QHBoxLayout* hlayout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;

    QLabel* lb_title = new QLabel(title);
    QLabel* lb_desc = new QLabel(desc);
    rb_color = new RoundLabel(this);
    rb_color->setMaximumWidth(SWITCH_WIDTH);

    lb_desc->setStyleSheet("color: rgb(50,50,50)");
    item_height = lb_title->fontMetrics().height() << 2;

    /*QPalette palette = lb_val->palette();
    palette.setColor(QPalette::Background, QColor(100, 2, 3, 255));
    lb_val->setAutoFillBackground(true);  //一定要这句，否则不行（实测加了也不行……）
    lb_val->setPalette(palette);
    lb_val->update();*/
    rb_color->setMainColor(c);

    vlayout->addWidget(lb_title);
    if (desc != "")
    {
        vlayout->addWidget(lb_desc);
    }
    hlayout->addLayout(vlayout);
    hlayout->addWidget(rb_color);
    //hLayout->addWidget(lb_val); // 因为改变不了颜色，所以就不显示了吧……

    if (tip != "")
    {
        this->setToolTip(tip);
    }

    this->setLayout(hlayout);


}

/**
 * 添加不可更改的设置项
 * @param key   设置项关键词
 * @param title 设置项标题
 * @param desc  设置项描述
 * @param tip   设置项提示（鼠标悬浮）
 */
UserSettingsItem::UserSettingsItem(QString key, QString title, QString desc, QString tip)
	: key(key)
{
    QVBoxLayout* vLayout = new QVBoxLayout;

    QLabel* lb_title = new QLabel(title);
    QLabel* lb_desc = new QLabel(desc);

    lb_desc->setStyleSheet("color: rgb(50,50,50)");
    item_height = lb_title->fontMetrics().height() << 2;

    vLayout->addWidget(lb_title);
    if (desc != "")
    {
        vLayout->addWidget(lb_desc);
    }

    if (tip != "")
    {
        this->setToolTip(tip);
    }

    this->setLayout(vLayout);
}

/**
 * 添加设置项分组标题
 * @param key   关键词
 * @param title 标题
 * @param desc  描述
 */
UserSettingsItem::UserSettingsItem(QString group_key, QString title, QString desc)
	: key(group_key)
{
    Q_UNUSED(desc);
    QLabel* lb_title = new QLabel(title);
    lb_title->setFont(QFont("Microsoft Yahei", 15));
    lb_title->setStyleSheet("color: rgb(50,50,50)");
    lb_title->setMargin(10);
    item_height = lb_title->fontMetrics().height() << 2;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(lb_title);
    setLayout(layout);
}

UserSettingsItem::UserSettingsItem(int kind)
{
    if (kind == 2) // 分割线
    {
        key = "splitter"; // 设置特定的分割线关键词，展开隐藏的项目

        QLabel* lb_title = new QLabel();
        lb_title->setStyleSheet("QWidget{background: rgb(100,100,100,30);}");
        //lb_title->setGeometry(0, 15, 10000, 1);
        lb_title->setMaximumHeight(2);
        lb_title->setToolTip("点击查看隐藏的设置项");
        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(lb_title);
        setLayout(layout);
    }
}

void UserSettingsItem::mouseReleaseEvent(QMouseEvent* e)
{
    QWidget::mousePressEvent(e);
	if (e->button() == Qt::LeftButton)
		emit signalClicked(this, key);
}

void UserSettingsItem::setVal(QString v)
{
	lb_val->setText(v);
}

void UserSettingsItem::setVal(int    v)
{
    nb_val->setShowNum(v);
}

void UserSettingsItem::setVal(bool   v)
{
	as->slotSwitch(v);
}

void UserSettingsItem::setVal(QColor v)
{
    /*lb_val->clear();
	QPalette palette;
    palette.setColor(QPalette::Background, v);
    lb_val->setAutoFillBackground(true);  //一定要这句，否则不行
    lb_val->setPalette(palette);
    lb_val->update();*/
    rb_color->setMainColor(v);
}

int UserSettingsItem::getHeight()
{
    return item_height + 3; // 这个 3 是为了避免有些无法显示完全的地方
}

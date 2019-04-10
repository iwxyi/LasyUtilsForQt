#ifndef USERSETTINGSITEM_H
#define USERSETTINGSITEM_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QColor>
#include <QPalette>
#include <QList>
#include <QMouseEvent>
#include "roundlabel.h"
#include "numberlabel.h"
#include "globalvar.h"
#include "aniswitch.h"

#define GROUPS_HEIGHT 50
#define ITEMS_HEIGHT 50
#define SWITCH_WIDTH 40

/**
 * 设置窗口的Item控件
 */
class UserSettingsItem : public QWidget
{
	Q_OBJECT
public:
    UserSettingsItem(QString key, QString title, QString desc, QString tip, QString v);
    UserSettingsItem(QString key, QString title, QString desc, QString tip, int v);
    UserSettingsItem(QString key, QString title, QString desc, QString tip, bool v);
    UserSettingsItem(QString key, QString title, QString desc, QString tip, QColor c);
    UserSettingsItem(QString key, QString title, QString desc, QString tip);
    UserSettingsItem(QString group_key, QString title, QString desc); // 分组
    UserSettingsItem(int kind);

    void setVal(QString v);
    void setVal(int     v);
    void setVal(bool    v);
    void setVal(QColor  v);

    int getHeight();

protected:
    void mouseReleaseEvent(QMouseEvent* e);

signals:
	void signalClicked(UserSettingsItem* item, QString key);

private:
	AniSwitch* as;
	QLabel* lb_val;
    RoundLabel* rb_color;
    NumberLabel* nb_val;
	QString key;
    int item_height;
};

#endif // USERSETTINGSITEM_H

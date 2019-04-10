/**
 * 全局宏定义
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <QString>


// ====标题栏 ====
#define BUTTON_HEIGHT 30 // 按钮高度
#define BUTTON_WIDTH 30  // 按钮宽度
#define TITLE_HEIGHT 30  // 标题栏高度

// ==== 布局 ====
#define CUTTING_SPACE 0  // 切掉的布局控件间宽度

// ==== NovelDir Role ====
#define DRole_CHP_NAME 0
#define DRole_CHP_NUM 1
#define DRole_CHP_NUM_CN 2
#define DRole_CHP_DETAIL 3
#define DRole_CHP_ISROLL 10
#define DRole_CHP_ISHIDE 4
#define DRole_CHP_STEMP 50
#define DRole_CHP_OPENING 100
#define DRole_ROLL_SUBS 11
#define DRole_ROLL_COUNT 12
#define DRole_CHP_FULLNAME 13
#define DRole_RC_ANIMATING 14
#define DRole_RC_SEARCH 15
#define DRole_CR_COUNT 16
#define DRole_ROLL_NAMES 17
#define DRole_CHP_ROLLINDEX 18
#define DRole_CHP_CHPTINDEX 19

#define DIR_DEVIATE 10      // 目录左边的距离
#define DIR_DEVIATE_ADD 20  // 章节比分卷靠后的距离

// ==== 文件 ====
#define NOVELDIRFILENAME "dir.txt"


// ==== 控件 ====
#define TRANSPARENT_SHOW_KIND_NOVEL_INFO 3


// ==== 引导 ====
#define LINE_GUIDE_NONE 0
#define LINE_GUIDE_CREATE_BOOK 1


#endif // DEFINES_H

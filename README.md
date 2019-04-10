# Qt小白工具类

Qt懒人专用Util集合，包含常用（我自己用到）的工具类

目前用到的项目：[写作天下](https://github.com/MRXY001/WriterFly)

网络见：[智能会议室管理系统](https://github.com/MRXY001/EasyMeeting)

> 小白（我这样的）专用！（其实是自用）
> 不适合那些大佬！



## 目录

**Globals/**

- globalvar    全局变量，要全局用到的都可以放这里来
- defines    一些宏定义（类似Android资源文件），比如程序名称、UserRole
- RuntimeInfo    程序运行状态，存储运行路径、存储路径等

**Utils/**

- FileUtil
- NetworkUtil
- StringUtil

**Settings**

- Settings    应用程序设置类Util，统一保存/读取设置项
- USettings    继承Settings，针对应用程序定制，建议放到GlobalVar中设置为全局



## 示例

### 读写txt文件

```C++
writeTextFile(rt->DATA_PATH+"tmp/a.txt", "存储内容"); // rt是RuntimeInfo的实例

QString str = readTextFile(rt->DATA_PATH+"tmp/a.txt"); // 读取txt文件
```

> 注意：有个很怪的bug，txt文件中的`<title>`标签后面的内容，怎么读都读不出来……



### 文件/文件夹操作

```C++
ensureFileExist(rt->DATA_PATH+"tmp/a.txt"); // 确保文件存在
ensureDirExist(rt->DATA_PATH+"tmp"); // 确保文件夹存在
if (isFileExist(rt->DATA_PATH+"tmp/a.txt")) ; // 判断文件是否存在
copyFile2(path1, path2); // 复制文件，若path2存在则覆盖
```



### 保存应用程序设置

```C++
us->setVal("open_time", rt->getTimestamp()); // 重载，可以直接保存（包括QColor）

qint64 a = us->getInt("open_time");
```



### 一行代码联网

最简单的例子

```C++
QString content = NetworkUtil::getHttpSource(url);
```



登录的例子

```C++
QStringList params = { "username", username, "password", password };
ConnectUtil* con = new ConnectUtil("login", params); // 直接联网，POST
connect(con, SIGNAL(signalFinished(QString)), this, SLOT(slotLoginFinished(QString))); // 信号槽

void LoginWindow::slotLoginFinished(QString content)
{
    QString result = getXml(content, "result");
    if (result == "" || result == "0") {
        QMessageBox::critical(this, "登录", "登录失败！\n"+result);
        return ;
    }
    /* ... */
}
```



### 应用程序更新

多线程更新，比较多，看写作天下吧
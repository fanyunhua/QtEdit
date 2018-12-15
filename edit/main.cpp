#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "QIcon"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //定义主窗口
    MainWindow w;
//     w.show();
//    return a.exec();
    //登陆窗口
    LoginDialog login;
    //显示登陆窗口
    login.show();
    //注意----这里使用png格式图片
    QIcon win(":/imgs/imgs/user_Login.png");
    w.setWindowTitle("主界面");
    w.setWindowIcon(win);
    QIcon win2(":/imgs/imgs/win.png");
    login.setWindowTitle("登陆");
    login.setWindowIcon(win2);
    if(login.exec()==QDialog::Accepted)//判断login窗口的登陆状态
    {
        w.show();
        return a.exec();
    }
    /**
     * 如果不注释掉下面一行会引起注册/登陆界面已关闭，但程序仍在运行的bug
     * return a.exec();
     **/
}

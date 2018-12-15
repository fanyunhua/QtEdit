#include "logindialog.h"
#include "ui_logindialog.h"
#include "databasehelper.h"
#include "QDebug"
#include "QMessageBox"
#include "QPalette"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->QButtonReg,SIGNAL(clicked()),this,SLOT(onReg()));
    connect(ui->QButtonLogin,SIGNAL(clicked()),this,SLOT(onLogin()));
}

databasehelper dba;
LoginDialog::~LoginDialog()
{

    delete ui;
}

int LoginDialog::onReg()//注册函数
{
    QString name = ui->QLineName->text();//获取用户输入
    QString pwd = ui->QLinePwd->text();
    if(name.length()!=0&&pwd.length()!=0)//对输入的内容进行判断
    {
       bool db = dba.getConn();//获取数据库连接
       if(!db)
       {
           qDebug() << "error open database failed ";
       }
       else
       {
           bool createTable = dba.createTable();//创建数据表
           if(!createTable)
           {
               qDebug() <<"create table failed";
           }
           else
           {
                qDebug()<<"table created";
                bool insert = dba.insertData(name,pwd);//插入数据
                if(!insert)
                {
                    qDebug()<< "操作失败";
                }
                else
                {
                    QMessageBox::information(this,"提示","注册成功");
                    qDebug()<< "registered successfully";
                    dba.close();
                }
           }
       }
        //dba.close();//关闭数据库
    }
    else
    {
        QMessageBox::information(this,"警告","用户名或密码不能为空");

    }
    return 0;
}
int LoginDialog::onLogin()
{
    QString name = ui->QLineName->text();//获取用户输入
    QString pwd = ui->QLinePwd->text();
    if(name.length()!=0&&pwd.length()!=0)//对输入的内容进行判断
    {
       bool db = dba.getConn();//获取数据库连接
       if(!db)
       {
           qDebug() << "error open database failed ";
       }
       else
       {
           bool state = dba.login(name,pwd);
           if(!state)
           {
               QMessageBox::information(this,"警告","用户名或密码不正确");

           }
           else
           {
                //这一句是告诉主窗口：我的状态改变了
                accept();//这一句很重要....跳到主窗口
               qDebug()<<"login successfully";
               return 1;
           }
       }
    }
    else
    {
        QMessageBox::information(this,"警告","用户名或密码不能为空");
    }
    return 0;
}

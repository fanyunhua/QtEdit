#include "databasehelper.h"
#include "QtSql/QSqlDatabase"
#include "QDebug"
#include "QtSql/QSqlQuery"
#include "QString"
databasehelper::databasehelper(){}

QSqlDatabase db;

databasehelper::~databasehelper(){}


bool databasehelper::getConn()
{

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        //获取数据库连接
        db = QSqlDatabase::database("qt_sql_default_connection");
         qDebug() <<"connect get successful";
         return true;
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");//获取数据库驱动
        db.setDatabaseName("MY_DATABASE.db");//创建数据库
        db.setUserName("fanyuhua");//sqlite可以省略
        db.setPassword("fanyuhua");
        qDebug() <<"database created";
        if(!db.open())
        {
            qDebug() <<"Failed open the database";
        }
        else
        {
            qDebug() <<"open database successful";
        }
        return true;
    }
    return false;
}
bool databasehelper::createTable()
{
    QSqlQuery sqlQuery;
    QString table_name = "login";
    bool findTableName = selectTabele(table_name);  //调用静态函数查看表是否已经被创建
    if(!findTableName)
    {
        QString sql = "create table login (name varchar(30), password varchar(30))";
        sqlQuery.prepare(sql);        //执行sql语句创建table
        if(!sqlQuery.exec())
        {
            qDebug() <<"the table create failed";
        }
        else
        {
            qDebug() << "Table created!";
            return true;//创建成功返回true
        }
    }

    return true;//表已存在可以使用，返回true
}
bool databasehelper::insertData(QString name,QString pwd)
{
    QSqlQuery sqlQuery;
    QString sql_insert = "insert into login values( '";
    QString sql2 = sql_insert.append(name.append("','").append(pwd.append("');")));//构造sql语句
    qDebug()<< sql2;
    sqlQuery.prepare(sql2);
    if(!sqlQuery.exec())
    {
        qDebug() <<"insert data  failed";
    }
    else
    {
        qDebug() <<"insert data  successful";
        return true;//插入成功
    }

    return false; //failed
}
bool databasehelper::selectTabele(QString tableName)
{
    QSqlQuery sqlQuery;
    QString sql = "select name from sqlite_master;";
    sqlQuery.prepare(sql);
    if(!sqlQuery.exec())
    {
        qDebug()<<"select table name failed";
    }
    else
    {
        while(sqlQuery.next())
        {
            QString table_name = sqlQuery.value(0).toString();//取出表名
           if(tableName!=table_name){           }//这一句暂时没什么用
           else
           {
               return true;//表已经存在，返回true
           }
        }
    }
    return false;//未查询到该表，返回false
}
bool databasehelper::login(QString name,QString pwd)
{
    QSqlQuery sqlQuery;
    QString sql = "select * from login";
    sqlQuery.prepare(sql);
    if(!sqlQuery.exec())
    {
        qDebug()<< "select * failed";
    }
    else
    {
        while(sqlQuery.next())
        {
            if(name==sqlQuery.value(0)&&pwd==sqlQuery.value(1))
            {
                return true;
            }
        }
    }
    return false;
}

void databasehelper::close()
{
    db.close();//关闭数据库
}

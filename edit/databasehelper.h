#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H


#include "QtSql/QSqlDatabase"
#include "QString"
class databasehelper
{

public:
    databasehelper();
    ~databasehelper();
    bool getConn();
    bool createTable();
    bool insertData(QString name,QString pwd);
    bool selectTabele(QString tableName);
    void close();
    bool login(QString name,QString pwd);
};
static bool selectTabele(QString tableName);
#endif // DATABASEHELPER_H

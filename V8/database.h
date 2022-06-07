#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>

#define DATABASE_NAME "bd_lauriou_tanguy"
#define CONNECT_TYPE "QODBC"
class Database
{
public:
    Database();
    bool openDataBase();
    void closeDataBase();

private:
    QSqlDatabase mydb;
};

#endif // DATABASE_H

#include "database.h"
#include <QDebug>

Database::Database()
{

}

bool Database::openDataBase()
{
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);
    if(mydb.open()) {
        qDebug()<<"base de données ouverte";
        return true;
    }
    else
        return false;
}

void Database::closeDataBase()
{
    mydb.close();
    qDebug()<<"basefermer";
}

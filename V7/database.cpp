#include "database.h"

Database::Database()
{

}


bool Database::openDataBase()
{
mydb = QSqlDatabase::addDatabase("QODBC");
mydb.setDatabaseName(DATABASE_NAME);
bool ok = mydb.open();
return ok;
}

void Database::closeDataBase()
{
mydb.close();
}


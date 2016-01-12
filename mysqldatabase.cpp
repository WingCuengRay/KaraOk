#include "mysqldatabase.h"


MysqlDatabase::MysqlDatabase(QString dbType)
{
    db = QSqlDatabase::addDatabase(dbType);


    return;
}

bool MysqlDatabase::openDataBase(QString hostName, QString dbName)
{
    db.setHostName(hostName);
    db.setDatabaseName(dbName);
    db.setUserName("ray");
    db.setPassword("leiying");

    bool ret = db.open();
    if(ret)
        qDebug() << "Open " << dbName << "successful!";
    else
    {
        qDebug() << "Open Error" << endl ;
        qDebug() << db.lastError().text();

        return false;
    }

    return true;
}


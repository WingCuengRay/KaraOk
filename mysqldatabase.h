#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include <QtSql>
#include <QDebug>

class MysqlDatabase
{
public:
    MysqlDatabase(QString dbType="QMYSQL");
    bool openDataBase(QString hostName = "localhost", QString dbName = "KaraOk");

private:
    QSqlDatabase db;

signals:

public slots:
};

#endif // MYSQLDATABASE_H

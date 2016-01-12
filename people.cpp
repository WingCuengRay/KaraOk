#include "people.h"
#include "mysqldatabase.h"
#include <stdio.h>
#include <string>
#include <QDebug>

extern MysqlDatabase mydat;

bool Admin::Login()
{
    QSqlQuery q;

    try
    {
        if(!q.exec("SELECT AdID, AdPd, AdNum FROM Admin"))
            throw "SELECT error!";
        while(q.next())
        {
            QString res_id = q.value(0).toString();
            QString res_pw = q.value(1).toString();
            if(res_id == People::id && res_pw == People::passwd)
            {
                isLogin = true;
                AdNum = q.value(2).toInt();
                return true;
            }

        }
    }
    catch(QString err)
    {
        qDebug() << err;
    }

    return false;
}


bool User::Login()
{
    QSqlQuery q;

    try
    {
        if(!q.exec("SELECT UID, UPd FROM User"))
            throw "SELECT error!";
        while(q.next())
        {
            QString res_id = q.value(0).toString();
            QString res_pw = q.value(1).toString();
            if(res_id == People::id && res_pw == People::passwd)
            {
                isLogin = true;
                return true;
            }

        }
    }
    catch(QString err)
    {
        qDebug() << err;
    }

    return false;

}




bool Admin::addSinger(QString name, Sex sex, QString Abbr, QString Loc)
{
    QByteArray _name = name.toUtf8();
    QByteArray _Abbr = Abbr.toUtf8();
    QByteArray _Loc = Loc.toUtf8();
    std::string _sex;
    char s[200];
    QSqlQuery query;

    try
    {
        if(sex == Male)
            _sex = "M";
        else
            _sex = "F";
        sprintf(s, "INSERT INTO Singer VALUES('%s', '%s', '%s', '%s')",
                _name.data(), _sex.c_str(), _Loc.data(),_Abbr.data());
        bool res = query.exec(s);
        if(!res)
            throw "INSERT Singer error!";

        QByteArray _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
        sprintf(s, "INSERT INTO Operation(AdNum, OpTime, OpType, OpObj) VALUES(%d, '%s', '添加歌手', '%s')",
                AdNum, _time.data(), _name.data());
        if( !query.exec(s) )
        {
            throw "INSERT Operation error!";
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        qDebug() << query.lastError();
        return false;
    }

    return true;
}



bool Admin::delSinger(QString name)
{
    QSqlQuery q;
    QByteArray _name = name.toUtf8();
    char s[200];

    try
    {
        sprintf(s, "DELETE FROM Singer WHERE Name = '%s'", _name.data());
        if(!q.exec(s))
        {
            throw "DELECT Singer error!";
        }

        QByteArray _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
        sprintf(s, "INSERT INTO Operation(AdNum, OpTime, OpType, OpObj) VALUES(%d, '%s', '删除歌手', '%s')",
                AdNum, _time.data(), _name.data());
        if( !q.exec(s) )
        {
            throw "INSERT Operation error!";
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        qDebug() << q.lastError();
        return false;
    }

    return true;
}


bool Admin::addSong(QString songName, QString singerName, QString Abbre, QString Dir, QString Lang, QString Sort)
{
    QByteArray _songName = songName.toUtf8();
    QByteArray _singerName = singerName.toUtf8();
    QByteArray _Abbre = Abbre.toUtf8();
    QByteArray _Lang = Lang.toUtf8();
    QByteArray _Sort = Sort.toUtf8();
    QByteArray _Dir = Dir.toUtf8();
    char s[200];
    QSqlQuery q;

    try
    {
        sprintf(s, "INSERT INTO Song(SongName, SingerName, Lang, Abbre, Sort, Dir) VALUES('%s', '%s', '%s', '%s','%s', '%s')",
                _songName.data(), _singerName.data(), _Lang.data(), _Abbre.data(), _Sort.data(), _Dir.data());
        bool res = q.exec(s);

        if(!res)
            throw "INSERT Song error!";

        QByteArray _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
        sprintf(s, "INSERT INTO Operation(AdNum, OpTime, OpType, OpObj) VALUES(%d, '%s', '添加歌曲', '%s')",
                AdNum, _time.data(), _songName.data());
        if( !q.exec(s) )
        {
            throw "INSERT Operation error!";
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        qDebug() << q.lastError();
        return false;
    }

    return true;
}


bool Admin::delSong(QString songName)
{
    QSqlQuery q;
    QByteArray _songName = songName.toUtf8();
    char s[200];

    try
    {
        sprintf(s, "DELETE FROM Song WHERE SongName = '%s'", _songName.data());
        if(!q.exec(s))
            throw "DELETE Song error!";

        QByteArray _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
        sprintf(s, "INSERT INTO Operation(AdNum, OpTime, OpType, OpObj) VALUES(%d, '%s', '删除歌曲', '%s')",
                AdNum, _time.data(), _songName.data());
        if( !q.exec(s) )
        {
            throw "INSERT Operation error!";
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        qDebug() << q.lastError();
        return false;
    }

    return true;
}



bool Admin::addUser(QString UID, QString pd, QString name)
{
    QSqlQuery q;
    char s[200];

    try
    {
        if(!isLogin)
            throw "Not identified!";

        QByteArray _uid = UID.toUtf8();
        sprintf(s, "SELECT * FROM User WHERE UID = '%s'", _uid.data());
        if( !q.exec(s) )
            throw "SELECT Error!";
        if(q.next())
            throw "UID has already been occupied!";

        QByteArray _pd = pd.toUtf8();
        QByteArray _name = name.toUtf8();
        sprintf(s, "INSERT INTO User VALUES('%s', '%s', '%s', NULL)", _uid.data(), _pd.data(), _name.data());
        if(!q.exec(s))
            throw "Insert Error";

        QByteArray _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
        sprintf(s, "INSERT INTO Operation(AdNum, OpTime, OpType, OpObj) VALUES(%d, '%s', '添加会员', '%s')",
                AdNum, _time.data(), _uid.data());
        if( !q.exec(s) )
        {
            throw "INSERT Operation error!";
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        qDebug() << q.lastError();
        return false;
    }

    return true;
}


bool Admin::delUser(QString UID)
{
    QSqlQuery q;
    char s[200];

    try
    {
        if(!isLogin)
            throw "Not identified!";
        QByteArray _uid = UID.toUtf8();
        sprintf(s, "DELETE FROM User WHERE UID = '%s'", _uid.data());
        if(!q.exec(s))
            throw "DELETE Error!UID Not Existed.";

        QByteArray _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
        sprintf(s, "INSERT INTO Operation(AdNum, OpTime, OpType, OpObj) VALUES(%d, '%s', '删除会员', '%s')",
                AdNum, _time.data(), _uid.data());
        if( !q.exec(s) )
        {
            throw "INSERT Operation error!";
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        qDebug() << q.lastError();
        return false;
    }

    return true;
}



bool User::addFavorSong(int songNum)
{
    QSqlQuery q;
    char s[100];
    QByteArray _id = id.toUtf8();

    try
    {
        if(!isLogin)
            throw "Unidentified user";
        sprintf(s, "SELECT FavorSong FROM User WHERE UID = '%s'", _id.data());
        if( !q.exec(s) )
            throw "Select error!";
        if(!q.next())
            throw "Error.No record!";

        QString res = q.value(0).toString();
        res = res + QString::number(songNum, 10) + ';';
        QByteArray _res = res.toUtf8();

        sprintf(s, "UPDATE User SET FavorSong = '%s' WHERE UID = '%s'", _res.data(), _id.data());
        if( !q.exec(s) )
            throw "Update error!";
    }
    catch(const char *err)
    {

        qDebug() << err;
        qDebug() << q.lastError();
        return false;
    }

    return true;
}

bool User::delFavorSong(int songNum)
{
    QSqlQuery q;
    char s[100];
    QByteArray _id = id.toUtf8();

    try
    {
        if(!isLogin)
            throw "Unidentified user";
        sprintf(s, "SELECT FavorSong FROM User WHERE UID = '%s'", _id.data());
        if( !q.exec(s) )
            throw "Select error!";
        if(!q.next())
            throw "Error.No record!";

        QString res = q.value(0).toString();
        QStringList resList = res.split(";");

        resList.removeAll(QString::number(songNum, 10));
        res = resList.join(";");

        QByteArray _res = res.toUtf8();
        sprintf(s, "UPDATE User SET FavorSong = '%s' WHERE UID = '%s'", _res.data(), _id.data());
        if( !q.exec(s) )
            throw "Update error!";
    }
    catch(const char *err)
    {

        qDebug() << err;
        qDebug() << q.lastError();
        return false;
    }

    return true;
}


QStringList *User::getFavorSong()
{
    QSqlQuery q;
    char s[100];
    QByteArray _id = id.toUtf8();

    try
    {
        if(!isLogin)
            throw "Unidentified user";
        sprintf(s, "SELECT FavorSong FROM User WHERE UID = '%s'", _id.data());
        if( !q.exec(s) )
            throw "Select error!";
        if(!q.next())
            throw "Error.No record!";

        QString res = q.value(0).toString();
        QStringList *resList = new QStringList(res.split(";"));

        return resList;
    }
    catch(const char *err)
    {

        qDebug() << err;
        qDebug() << q.lastError();
        return NULL;
    }
}





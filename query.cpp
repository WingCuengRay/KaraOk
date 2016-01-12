#include "query.h"

/**
 * @brief songAbbreOrder
 * @param songAbbre
 * @return 符合条件的歌曲名与歌手
 * @func  按歌名首拼音点歌
 */
QVector< QPair<QString, QString> > *songAbbreOrder(QString songAbbre)
{
    QSqlQuery q;
    char s[100];
    QByteArray _songAbbre = songAbbre.toUtf8();
    QVector< QPair<QString, QString> > *res;

    try
    {
        sprintf(s, "SELECT SongName, SingerName FROM Song WHERE Abbre = '%s'", _songAbbre.data());
        if(!q.exec(s))
            throw "songAbbreOrder() SELECT error!";
        res = new QVector< QPair<QString, QString> >;
        while(q.next())
        {
            res->push_back(QPair<QString, QString>(q.value(0).toString(), q.value(1).toString()));
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        delete res;
        return NULL;
    }

    return res;
}


/**
 * @brief singerAbbreOrder
 * @param singerAbbre
 * @return 符合条件的歌曲名与歌手
 * @func  按歌手名首拼音点歌
 */
QVector< QPair<QString, QString> > *singerAbbreOrder(QString singerAbbre)
{
    QSqlQuery q;
    char s[200];
    QByteArray _singerAbbre = singerAbbre.toUtf8();
    QVector< QPair<QString, QString> > *res;

    try
    {
        sprintf(s, "SELECT SongName, SingerName FROM Song,Singer \
                    WHERE Singer.Abbre = '%s' AND Singer.Name = Song.SingerName", _singerAbbre.data());
        if(!q.exec(s))
            throw "singerAbbreOrder() SELECT error!";
        res = new QVector< QPair<QString, QString> >;
        while(q.next())
        {
            res->push_back(QPair<QString, QString>(q.value(0).toString(), q.value(1).toString()));
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        delete res;
        return NULL;
    }

    return res;
}


/**
 * @brief singerAbbreOrder2
 * @param singerAbbre
 * @func   按歌手名首拼音搜索歌手
 * @return 返回歌手清单
 */
QVector<QString> *singerAbbreOrder2(QString singerAbbre)
{
    QSqlQuery q;
    char s[100];
    QByteArray _singerAbbre = singerAbbre.toUtf8();
    QVector<QString> *res;

    try
    {
        sprintf(s, "SELECT SingerName FROM Singer \
                    WHERE Singer.Abbre = '%s'", _singerAbbre.data());
        if(!q.exec(s))
            throw "singerAbbreOrder SELECT error!";
        res = new QVector<QString>;
        while(q.next())
        {
            res->push_back(q.value(0).toString());
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        delete res;
        return NULL;
    }

    return res;
}



/**
 * @brief LocOrder
 * @param Loc
 * @func  按地区搜索歌手
 * @return 返回歌手地区歌手列表
 */
QVector<QString> *LocOrder(QString Loc)
{
    QSqlQuery q;
    char s[100];
    QByteArray _Loc = Loc.toUtf8();
    QVector<QString> *res;

    try
    {
        sprintf(s, "SELECT SingerName FROM Singer \
                    WHERE Singer.Loc = '%s'", _Loc.data());
        if(!q.exec(s))
            throw "LocOrder() SELECT error!";
        res = new QVector<QString>;
        while(q.next())
        {
            res->push_back(q.value(0).toString());
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        delete res;
        return NULL;
    }


    return res;
}

/**
 * @brief LangOrder
 * @param Lang
 * @func  按语言查找歌曲
 * @return 返回符合条件的歌曲和歌手列表
 */
QVector< QPair<QString, QString> > *LangOrder(QString Lang)
{
    QSqlQuery q;
    char s[200];
    QByteArray _Lang = Lang.toUtf8();
    QVector< QPair<QString, QString> > *res;

    try
    {
        sprintf(s, "SELECT SongName, SingerName FROM Song \
                    WHERE Song.Lang = '%s'", _Lang.data());
        if( !q.exec(s) )
            throw "LangOrder SELECT error!";
        res = new QVector< QPair<QString, QString> >;
        while(q.next())
        {
            res->push_back(QPair<QString, QString>(q.value(0).toString(), q.value(1).toString()));
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        delete res;
        return NULL;
    }


    return res;
}



/**
 * @brief SortOrder
 * @param Sort
 * @func  按照分类点歌
 * @return 返回歌曲名和歌手列表
 */
QVector< QPair<QString, QString> > *SortOrder(QString Sort)
{
    QSqlQuery q;
    char s[200];
    QByteArray _Sort = Sort.toUtf8();
    QVector< QPair<QString, QString> > *res;

    try
    {
        sprintf(s, "SELECT SongName, SingerName FROM Song \
                    WHERE Song.Sort = '%s'", _Sort.data());
        if( !q.exec(s) )
            throw "SortOrder() SELECT error!";
        res = new QVector< QPair<QString, QString> >;
        while(q.next())
        {
            res->push_back(QPair<QString, QString>(q.value(0).toString(), q.value(1).toString()));
        }
    }
    catch(const char *err)
    {
        qDebug() << err;
        delete res;
        return NULL;
    }

    return res;
}



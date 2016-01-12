#ifndef PEOPLE_H
#define PEOPLE_H

#include <QString>
#include <QVector>

class People
{
public:

    People( QString i = "", QString p = "",QString n = "")    :
         id(i), passwd(p), name(n)
    { isLogin = false; }

    bool changePasswd(QString);
    virtual bool Login() = 0;

    QString name;
    QString id;
    QString passwd;
    bool isLogin;

private:


};



class User : public People
{
public:
    User(QString i = "", QString p = "",QString n = "")  :
        People(i, p, n)
    { }
    bool addFavorSong(int songNum);
    bool delFavorSong(int songNum);
    bool Login();
    QStringList *getFavorSong();

private:

};

enum Sex{Male, Female};


class Admin : public People
{
public:
    Admin( QString i = "", QString p = "")  :
        People(i, p, "")
    { }

    bool addSong(QString songName, QString singerName, QString Abbre, QString Dir = "/ray", QString Lang = "粤语", QString Sort = "流行");
    bool delSong(QString songName);
    bool addSinger(QString name, Sex sex, QString Abbr, QString Loc="大陆");
    bool delSinger(QString name);
    bool addUser(QString UID, QString pd = "", QString name = "");
    bool delUser(QString UID);
    bool Login();

    int AdNum;

private:


};

#endif // PEOPLE_H

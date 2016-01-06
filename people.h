#ifndef PEOPLE_H
#define PEOPLE_H

#include <QString>
#include <QVector>

class People
{
public:
    People();
    void changePasswd();

private:
    QString name;
    QString id;
    QString passwd;
};



class User : People
{
public:
    bool addFavorSong(QString songName);
    bool delFavorSong(QString songName);

private:

};


class Admin : People
{
public:
    bool addSong(QString songName);
    bool delSong(QString songName);
    bool addSinger(QString name);
    bool delSinger(QString name);

};

#endif // PEOPLE_H

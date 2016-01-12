#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QDebug>
#include <stdio.h>
#include <vector>
#include "people.h"
#include "mysqldatabase.h"


QVector< QPair<QString, QString> > *songAbbreOrder(QString songAbbre);
QVector< QPair<QString, QString> > *singerAbbreOrder(QString singerAbbre);
QVector<QString> *singerAbbreOrder2(QString singerAbbre);
QVector<QString> *LocOrder(QString Loc);
QVector< QPair<QString, QString> > *LangOrder(QString Lang);
QVector< QPair<QString, QString> > *SortOrder(QString Sort);

#endif // QUERY_H


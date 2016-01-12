#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>
#include "mysqldatabase.h"
#include "people.h"
#include "logindlg.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    w.setFixedSize(800, 600);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    MysqlDatabase mydat("QMYSQL");
    mydat.openDataBase();


//    LoginDlg login;
    if(w.login.exec() == QDialog::Accepted)
    {
        w.setInformation();

        if(w.login.user != NULL)
        {
            w.setUserWindow();
        }
        else
        {
            w.setAdminWindow();
        }
        Admin ad1("ray","123456");
        User user1("TOM", "1234", "TOM");
        if(ad1.Login())
            qDebug() << "ad1 login sucessful!";

        w.show();
    }
    else
        return 0;



    return a.exec();
}


#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include "people.h"

namespace  Ui{
    class logindlg;
}

class LoginDlg  : public QDialog
{
    Q_OBJECT

public:
    LoginDlg(QWidget *parent = 0);
    ~LoginDlg();

    Admin *adm = NULL;
    User *user = NULL;

private:
    Ui::logindlg *ui;

signals:

public slots:
    void AdminLogin();
    void UserLogin();
};

#endif // LOGINDLG_H

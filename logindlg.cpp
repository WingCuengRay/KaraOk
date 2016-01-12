#include "logindlg.h"
#include "ui_logindlg.h"
#include <QTextCodec>
#include <QMessageBox>

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindlg)
{
    ui->setupUi(this);
    ui->lineEdit_pw->setEchoMode(QLineEdit::Password);

    connect(ui->Admin_login, SIGNAL(clicked(bool)), this, SLOT(AdminLogin()));
    connect(ui->User_login, SIGNAL(clicked(bool)), this, SLOT(UserLogin()));
}

LoginDlg::~LoginDlg()
{
    delete ui;
}



void LoginDlg::AdminLogin()
{
    QString id = ui->lineEdit_id->text();
    QString pw = ui->lineEdit_pw->text();

    adm = new Admin(id, pw);
    if( adm->Login() )
        accept();
    else
    {
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
        this->ui->lineEdit_id->clear();
        this->ui->lineEdit_pw->clear();
        this->ui->lineEdit_id->setFocus();
        delete adm;
        adm = NULL;
    }
}


void LoginDlg::UserLogin()
{
    QString id = ui->lineEdit_id->text();
    QString pw = ui->lineEdit_pw->text();

    user = new User(id, pw);
    if( user->Login())
        accept();
    else
    {
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
        this->ui->lineEdit_id->clear();
        this->ui->lineEdit_pw->clear();
        this->ui->lineEdit_id->setFocus();
        delete user;
        user = NULL;
    }
}


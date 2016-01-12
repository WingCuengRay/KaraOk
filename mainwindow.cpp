#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGLWidget>
#include <QGridLayout>
#include <QtOpenGL/QGLWidget>
#include <QDialog>
#include <QSqlQuery>
#include "people.h"
#include "logindlg.h"
#include <stdio.h>
#include <QDebug>
#include <QSqlError>

extern LoginDlg login;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInformation()
{
    if(login.adm != NULL)
    {
        ui->label_1->setText("身份： 管理员");
        ui->label_2->setText(QString("账号： ")+login.adm->id);
        ui->label_3->setText(QString("编号： ")+QString::number(login.adm->AdNum, 10));
        button1 = new QPushButton("歌曲管理");
        ui->verticalLayout_2->addWidget(button1, 0, Qt::AlignTop);
        connect(button1, SIGNAL(clicked(bool)), this, SLOT(showSongsInformation()));

        button1 = new QPushButton("歌手管理");
        ui->verticalLayout_2->addWidget(button1, 0, Qt::AlignTop);
        connect(button1, SIGNAL(clicked(bool)), this, SLOT(showSingerInformation()));

        button1 = new QPushButton("会员管理");
        ui->verticalLayout_2->addWidget(button1, 0, Qt::AlignTop);
        connect(button1, SIGNAL(clicked(bool)), this, SLOT(showUserInformation()));

        button1 = new QPushButton("操作记录查看");
        ui->verticalLayout_2->addWidget(button1, 0, Qt::AlignTop);
        connect(button1, SIGNAL(clicked(bool)), this, SLOT(showOpInformation()));

        connect(ui->pB_submit, SIGNAL(clicked(bool)), this, SLOT(on_pB_submit()));
        connect(ui->pB_add, SIGNAL(clicked(bool)), this, SLOT(on_pB_add()));
        connect(ui->pB_delete, SIGNAL(clicked(bool)), this, SLOT(on_pB_del()));
        connect(ui->pB_cancel, SIGNAL(clicked(bool)), this, SLOT(on_pB_cancel()));
    }
    else if(login.user != NULL)
    {
        ui->label_1->setText("身份： 会员");
        ui->label_2->setText(QString("账号： ")+login.user->id);
        ui->label_3->setText(QString("姓名： ")+login.user->name);

        button1 = new QPushButton("查看收藏歌曲");
        ui->verticalLayout->addWidget(button1);
        connect(this->button1, SIGNAL(clicked(bool)), this, SLOT(showFavorSong()));
    }
    else
    {

    }
}



void MainWindow::showFavorSong()
{
    static bool flag = 0;

    if(!flag)
    {
        QStringList* resList = login.user->getFavorSong();
        resList->removeAll("");

        QTableView *pTableView = new QTableView(0);
        mode = new QSqlTableModel(pTableView);
        ui->verticalLayout_2->addWidget(new QLabel("收藏歌曲"), 0, Qt::AlignHCenter);
        ui->verticalLayout_2->addWidget(pTableView);

        mode->setTable("Song");
        mode->setFilter("Num IN(" + resList->join(",") + ")");
        mode->select();
        mode->removeColumn(4);
        mode->removeColumn(5);
        pTableView->setModel(mode);
        pTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        flag = 1;
    }
}

/**
 * @brief MainWindow::setUserWindow
 * @func  如果是用户登陆，则开启OpenGl模式，并开启查询喜欢歌曲功能
 */
void MainWindow::setUserWindow()
{
    QGridLayout *mainLayout = new QGridLayout(ui->widget);
    nehewidget = new NeHeWidget(0, FALSE);
    nehewidget->setGeometry(0, 0, 1000,1000);
    nehewidget->setFocusPolicy(Qt::ClickFocus);
    mainLayout->addWidget(nehewidget);
}

void MainWindow::setAdminWindow()
{
//    tablewidget = new QTableWidget(ui->widget);
    mode = new QSqlTableModel(ui->tableView);
}


/**
 * @brief MainWindow::showSongsInformation
 * @func  显示歌曲信息的槽函数
 */
void  MainWindow::showSongsInformation()
{
    mode->removeRows(0, mode->rowCount());
    mode->setTable("Song");
    mode->setEditStrategy(QSqlTableModel::OnManualSubmit);
    mode->select();

    //mode->removeColumn(0);
    ui->tableView->setModel(mode);
    ui->table_name->setText("歌曲信息");
}



/**
 * @brief MainWindow::showSingerInformation
 * @func  显示歌手信息的槽函数
 */
void MainWindow::showSingerInformation()
{
    mode->removeRows(0, mode->rowCount());
    mode->setTable("Singer");
    mode->setEditStrategy(QSqlTableModel::OnManualSubmit);
    mode->select();

    //mode->removeColumn(0);
    ui->tableView->setModel(mode);
    ui->table_name->setText("歌手信息");
}


/**
 * @brief MainWindow::showUserInformation
 * @func  显示会员信息的槽函数
 */
void MainWindow::showUserInformation()
{
    mode->removeRows(0, mode->rowCount());
    mode->setTable("User");
    mode->setEditStrategy(QSqlTableModel::OnManualSubmit);
    mode->select();

    //mode->removeColumn(0);

    ui->tableView->setModel(mode);
    ui->table_name->setText("会员信息");
}



void MainWindow::showOpInformation()
{
    mode->removeRows(0, mode->rowCount());
    mode->setTable("Operation");
    mode->select();

    ui->tableView->setModel(mode);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_name->setText("操作记录");
}



/**
 * @brief MainWindow::on_pB_submit
 * @func  提交修改的槽
 */
void MainWindow::on_pB_submit()
{
    mode->database().transaction();

    if(mode->submitAll())
        mode->database().commit();
    else
    {
        mode->database().rollback();
        QMessageBox::warning(this, "tableModel", "数据库错误："+mode->lastError().text());
    }
}


void MainWindow::on_pB_cancel()
{
    mode->revertAll();
}


/**
 * @brief MainWindow::on_pB_del
 * @func  删除选中行的槽函数
 */
void MainWindow::on_pB_del()
{
    int curRow = ui->tableView->currentIndex().row();

    mode->removeRow(curRow);

    int ok = QMessageBox::warning(this, "删除该行", "你确定删除该行吗？",
                                  QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
        mode->revertAll();
    else
        mode->submitAll();
}


/**
 * @brief MainWindow::on_pB_add
 * @func  增加一个记录的槽函数
 */
void MainWindow::on_pB_add()
{
    int rowNum = mode->rowCount();
    mode->insertRow(rowNum);
}

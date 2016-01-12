#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nehewidget.h"
#include "logindlg.h"
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setInformation();
    void setUserWindow();
    void setAdminWindow();
    LoginDlg login;

private:
    Ui::MainWindow *ui;
    NeHeWidget *nehewidget;
    QPushButton *button1;
    QTableView *tablewidget;
    QSqlTableModel *mode;

public slots:
    void showFavorSong();
    void showSongsInformation();
    void showSingerInformation();
    void showUserInformation();
    void showOpInformation();

    void on_pB_submit();
    void on_pB_cancel();
    void on_pB_del();
    void on_pB_add();
};


#endif // MAINWINDOW_H

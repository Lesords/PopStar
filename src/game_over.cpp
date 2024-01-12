#include "game_over.h"
#include "mainwindow.h"
#include "popstar.h"
#include "ui_game_over.h"

Game_Over::Game_Over(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game_Over)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));        // 背景为白色
    setAttribute(Qt::WA_DeleteOnClose);     // 窗口关闭时自动释放内存
}

Game_Over::~Game_Over()
{
    delete ui;
}

void Game_Over::set_score(int score) {      // 设置游戏得分
    ui->score->setText(QString::number(score));
}

void Game_Over::on_home_clicked()           // 返回主界面
{
    this->close();
    MainWindow *w = new MainWindow();
    w->show();
}

void Game_Over::on_restart_clicked()        // 重新开始游戏
{
    this->close();
    popstar *p = new popstar();
    p->show();
}

#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <QWidget>

namespace Ui {
class Game_Over;
}

class Game_Over : public QWidget
{
    Q_OBJECT

public:
    explicit Game_Over(QWidget *parent = 0);
    void set_score(int score);          // 设置最后得分
    ~Game_Over();

private slots:
    void on_home_clicked();             // 返回主界面

    void on_restart_clicked();          // 重新开始游戏

private:
    Ui::Game_Over *ui;
};

#endif // GAME_OVER_H

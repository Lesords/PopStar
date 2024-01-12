#ifndef POPSTAR_H
#define POPSTAR_H

#include <QWidget>
#include <QtCore>
#include <QFile>
#include <QTime>
#include <QRect>
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QDebug>
#include <QMouseEvent>

#include <queue>
#include <vector>

namespace Ui {
class popstar;
}

struct star_node{
    int color, fall_len, move_len;
    QPoint left_top;                // 当前点左上角的坐标
    star_node(): color(-1), fall_len(0), move_len(0) {}
};
struct node{
    int x, y;
};

class popstar : public QWidget
{
    Q_OBJECT

public:
    explicit popstar(QWidget *parent = 0);
    ~popstar();

    bool reload();  // 加载存档内容


private:
    QRect game_area;    // 游戏区域
    QPoint left_top, right_bottom, p_star;  // 游戏区域点的左上角、右下角以及星星大小
    QPixmap pixmap;
    QPixmap pstar[5];   // 对应的星星图片
    star_node star_map[10][10];             // 记录对应星星的状态
    int nextt[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};   // 四个方向
    int level, target, score, hammer;       // 关卡，关卡分数，当前分数，是否使用锤子道具
    int moving, passing;                    // 是否处于一个鼠标事件内，当前关卡是否通过


protected:
    void paintEvent(QPaintEvent *);         // 重写窗体重绘事件
    void mousePressEvent(QMouseEvent *e);   // 重写鼠标点击事件
    void init(bool reload = false);         // 初始化对应星星的颜色
    int cal_num(int x, int y, int color);   // 计算附近相同颜色的星星数量
    void fall_star();                       // 星星下落
    void move_star();                       // 星星左移
    void clean_rest();                      // 消除剩余星星，并且判断是否可以进入下一关
    bool is_map(QPoint pos);
    bool is_map(int x, int y);
    bool is_over();                         // 判断游戏是否结束
    bool can_pop(int x, int y);             // 判断周围是否有相同颜色的星星
    void wait_ms(int x);                    // 延时函数
    void save();                            // 存档功能

private slots:
    void on_home_button_clicked();          // 返回主界面
    void on_update_button_clicked();        // 刷新道具
    void on_hammer_buton_clicked();         // 锤子道具

private:
    Ui::popstar *ui;
};

#endif // POPSTAR_H

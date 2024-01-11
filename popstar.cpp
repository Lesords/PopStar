#include "popstar.h"
#include "mainwindow.h"
#include "game_over.h"
#include "ui_popstar.h"

#include <iostream>
#include <Windows.h>

popstar::popstar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::popstar)
{
    ui->setupUi(this);

    this->setFixedSize(636, 350);       // 固定窗口大小
    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时自动释放内存

    p_star = QPoint(30, 30);            // 星星大小
    left_top = QPoint(180, 15);         // 左上角位置
    right_bottom = QPoint(498, 333);    // 右下角位置
    game_area = QRect(left_top, right_bottom);// 两个位置形成对应的星星区域

    pixmap = QPixmap(size());
    pixmap.fill(Qt::white);

    // 加载对应星星图片
    pstar[0].load(":/star/src/star1.png");
    pstar[1].load(":/star/src/star2.png");
    pstar[2].load(":/star/src/star3.png");
    pstar[3].load(":/star/src/star4.png");
    pstar[4].load(":/star/src/star5.png");

    // 初始化数据
    level = 1;      // 关卡
    target = 1000;  // 关卡分数
    score = 0;      // 当前分数
    passing = 0;    // 当前未通关
    moving = 0;     // 当前没有正在执行的鼠标事件
    hammer = 0;     // 当前没有使用锤子道具
    init();         // 初始化所有星星的颜色
}

popstar::~popstar()
{
    delete ui;
}

// 重写窗体重绘事件
void popstar::paintEvent(QPaintEvent *) {
    QPixmap pix = pixmap;
    QPainter painter_star(&pix);
    for(int i = 0;i < 10;i++) {
        for(int j = 0;j < 10;j++) {
            if(star_map[i][j].color == -1) continue;
            QPoint& cur = star_map[i][j].left_top;
            int id = star_map[i][j].color;
            painter_star.drawPixmap(QRect(cur, cur + p_star), pstar[id]);
        }
    }
    if(score >= target) {
        QPen pen_color;
        QFont font("华文新魏", 12);
        pen_color.setColor(QColor(255, 200, 35));
        painter_star.setPen(pen_color);
        painter_star.setFont(font);
        if(passing == 0) {
            passing = 1;
            Beep(666, 300);
            Beep(888, 300);
        }
        painter_star.drawText(90, 36, "恭喜通关");//绘制当前得分
    }

    painter_star.end();
    painter_star.begin(this);
    painter_star.drawPixmap(0,0,pix);

    ui->score->setText(QString::number(score));
    ui->target->setText(QString::number(target));
    ui->level->setText(QString::number(level));
}

// 重写鼠标点击事件
void popstar::mousePressEvent(QMouseEvent *e) {
    if(moving || !is_map(e->pos())) return;
    QPoint pos = e->pos() - left_top;
    int x = pos.y() / 32, y = pos.x() / 32; //x轴是从左到右，y轴是从上到下
    qDebug() << "x: " << x << " y: " << y;
    if(star_map[x][y].color == -1 || (!hammer &&!can_pop(x, y))) {
        qDebug() << "not working!";
        return;
    }

    moving = 1;
    if(hammer) {
        hammer = 0;
        this->setCursor(Qt::ArrowCursor);
        star_map[x][y].color = -1;
    }
    else {
        int num = cal_num(x, y, star_map[x][y].color);
        score += num*num*5;
    }

    Beep(466, 30);
    repaint();

    fall_star();
    move_star();
    moving = 0;
    if(is_over()) {
        clean_rest();
    }
}

// 初始化对应位置的星星颜色，reload表示只刷新存在星星的位置
void popstar::init(bool reload) {
    qsrand(QTime(0, 0, 0, 0).msecsTo((QTime::currentTime())));//设置一个随机种子
    qDebug() << "--开始初始化--\n";
    for(int i = 0;i < 10;i++) {
        for(int j = 0;j < 10;j++) {
            if(reload && star_map[i][j].color == -1) continue;
            star_map[i][j].color = qrand() % 5;              // 最多只有5种星星
            star_map[i][j].left_top = left_top + QPoint(j*32, i*32); //x轴是从左到右，y轴是从上到下
            star_map[i][j].fall_len = star_map[i][j].move_len = 0;
        }
    }
    for(int i = 0;i < 10;i++) {
        for(int j = 0;j < 10;j++) {
            std::cerr << star_map[i][j].color << " ";
        }
        std::cerr << "\n";
    }
    std::cerr << "----------------\n";
}

// 计算与 (x,y) 相连颜色为 color 的星星数量
int popstar::cal_num(int x, int y, int color) {
    std::queue<node> q;
    q.push({x, y});
    star_map[x][y].color = -1;
    int ans = 1;
    while(!q.empty()) {
        node now = q.front();q.pop();
        for(int i = 0;i < 4;i++) {
            int tx = now.x + nextt[i][0];
            int ty = now.y + nextt[i][1];
            if(tx < 0 || tx >= 10 || ty < 0 || ty >= 10) continue;
            if(star_map[tx][ty].color != color) continue;
            star_map[tx][ty].color = -1;
            ans++;
            q.push({tx, ty});
        }
    }
    qDebug() << "ans :" << ans;
    return ans;
}

// 实现星星下落效果
void popstar::fall_star() {
    std::vector<int> num(10);
    int max_siz = 0, siz = 0;
    for(int i = 9;i >= 0;i--) {
        for(int j = 0;j < 10;j++) {
            if(star_map[i][j].color == -1) num[j]++;
            else {
                star_map[i][j].fall_len = num[j]*32;
                max_siz = (std::max)(max_siz, num[j]*32);
            }
        }
    }
    std::vector<star_node> star_tmp;
    for(int i = 0;i < 10;i++) {
        for(int j = 0;j < 10;j++) {
            if(star_map[j][i].color == -1) continue;
            star_tmp.push_back(star_map[j][i]);
        }
        for(int j = 9;j >= 0;j--) {
            if(star_tmp.empty()) star_map[j][i].color = -1;
            else star_map[j][i] = star_tmp.back(), star_tmp.pop_back();
        }
    }
    siz = max_siz >= 96 ? 8 : 4;
    for(int i = 1;i <= max_siz/siz;i++) {
        for(int j = 0;j < 10;j++) {
            for(int k = 0;k < 10;k++) {
                if(star_map[j][k].color == -1) continue;
                if(star_map[j][k].fall_len == 0) continue;
                star_map[j][k].left_top.ry() += siz;
                star_map[j][k].fall_len -= siz;
            }
        }
        repaint();
        wait_ms(20);
    }
}

// 实现星星左移效果
void popstar::move_star() {
    int num = 0, siz = 0;
    for(int j = 0;j < 10;j++) {
        if(star_map[9][j].color == -1) num++;
        else if(num) {
            for(int i = 0;i < 10;i++) {// 整列都需要左移
                star_map[i][j].move_len = num * 32;
            }
        }
    }
    for(int j = 0;j < 10;j++) {
        if(star_map[9][j].color == -1) continue;
        if(star_map[9][j].move_len == 0) continue;
        for(int i = 0;i < 10;i++) {
            int pos = j - star_map[i][j].move_len / 32;
            star_map[i][pos] = star_map[i][j];
            star_map[i][j].color = -1;
        }
    }
    siz = num >= 3 ? 8 : 4;
    for(int i = 1;i <= num*32/siz;i++) {
        for(int j = 0;j < 10;j++) {
            for(int k = 0;k < 10;k++) {
                if(star_map[j][k].color == -1) continue;
                if(star_map[j][k].move_len == 0) continue;
                star_map[j][k].left_top.rx() -= siz;
                star_map[j][k].move_len -= siz;
            }
        }
        repaint();
        wait_ms(20);
    }
}

// 清空剩余星星，并且判断是否可以进入下一关
void popstar::clean_rest() {
    int cnt = 0;
    for(int j = 0;j < 10;j++) {
        for(int i = 0;i < 10;i++) {
            if(star_map[i][j].color != -1) {
                star_map[i][j].color = -1;
                cnt++;
                repaint();
                wait_ms(100);
            }
        }
    }
    score += (std::max)(0, 2000 - cnt*cnt*20);// 添加奖励分数
    if(score >= target) {
        level++;
        target += level % 3 ? 2000:3000;
        passing = 0;
        init();
        wait_ms(500);
        repaint();
    }
    else {
        this->close();
        Game_Over *g = new Game_Over();
        g->set_score(score);
        g->show();
    }
}

// 判断游戏是否结束（即不存在可消除的星星）
bool popstar::is_over() {
    for(int i = 0;i < 10;i++) {
        for(int j = 0;j < 10;j++) {
            if(star_map[i][j].color == -1) continue;
            if(can_pop(i, j)) return false;
        }
    }
    return true;
}

bool popstar::can_pop(int x, int y) {
    for(int i = 0;i < 4;i++) {
        int tx = x + nextt[i][0];
        int ty = y + nextt[i][1];
        if(tx < 0 || tx >= 10 || ty < 0 || ty >= 10) continue;
        if(star_map[tx][ty].color == star_map[x][y].color) {
            return true;
        }
    }
    return false;
}

bool popstar::is_map(int x, int y) {
    return x >= 180 && x <= 480 && y >= 16 && y <= 316;
}

bool popstar::is_map(QPoint pos) {
    return game_area.contains(pos);
}

// 等待x毫秒
void popstar::wait_ms(int x)
{
    QTime t;
    t.start();
    while(t.elapsed()<x)
        QCoreApplication::processEvents();
}

// 存档
void popstar::save() {
    QFile file("stars.info");
    if(file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);
        for(int i = 0;i < 10;i++) {
            for(int j = 0;j < 10;j++) {
                if(j) out << " ";
                out << star_map[i][j].color;
            }
            out << "\n";
        }
        out << level << " " << target << " " << score << " " << passing;
        qDebug() << "保存成功";
    }
    file.close();
}

// 读档
bool popstar::reload() {
    QFile file("stars.info");
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug() << file.errorString();
        return false;
    }
    QTextStream in(&file);
    qDebug() << "read file";
    bool ok;
    for(int i = 0;i < 10;i++) {
        QString oneLine = in.readLine();
        QStringList vals = oneLine.split(' ');
//        qDebug() << oneLine;
        for(int j = 0;j < vals.size();j++) {
            star_map[i][j].color = vals[j].toInt(&ok);
            star_map[i][j].left_top = left_top + QPoint(j*32, i*32);
            star_map[i][j].fall_len = star_map[i][j].move_len = 0;
//            qDebug() << vals[j] ;
        }
//        std::cerr << "\n";
    }
    QStringList vals = in.readLine().split(' ');
    level = vals[0].toInt(&ok), target = vals[1].toInt(&ok);
    score = vals[2].toInt(&ok), passing = vals[3].toInt(&ok);
    qDebug() << "file done\n";
    file.close();
    file.remove();
    return true;
}

// 返回主界面
void popstar::on_home_button_clicked()
{
    save();
    this->close();
    MainWindow *w = new MainWindow();
    w->show();
}

// 刷新道具
void popstar::on_update_button_clicked()
{
    init(1);
    ui->score->setText(QString::number(0));
    repaint();
}

// 锤子道具
void popstar::on_hammer_buton_clicked()
{
    if(hammer) {
        hammer = 0;
        this->setCursor(Qt::ArrowCursor);
    }
    else {
        this->setCursor(Qt::PointingHandCursor);
        hammer = 1;
    }
}

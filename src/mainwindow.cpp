#include "mainwindow.h"
#include "popstar.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭时自动释放内存

    QFile file("stars.info");
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) { // 如果不存在存档的话，按键失效
        ui->reload_button->setDisabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()    // 开始游戏
{
//    this->close();
    popstar *p = new popstar();
    p->show();
}

void MainWindow::on_reload_button_clicked() // 继续游戏
{
    this->close();
    popstar *p = new popstar();
    p->reload(); // 需要重新加载游戏数据
    p->show();
}

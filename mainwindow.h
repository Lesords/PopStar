#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();       // 开始游戏

    void on_reload_button_clicked();    // 继续游戏

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

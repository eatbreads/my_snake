#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include "config.h"
#include "mypushbutton.h"
#include <QPainter>
#include <snake.h>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <mypoint.h>
#include <QDebug>
#include <QString>
#include"food.h"
#include "gamemenu.h"
#include "ConfigFile.h"
#include "obstacle.h"
//int m_HighScore = 0;
class GamePlay : public QWidget
{
    Q_OBJECT
public:



    MyPushButton *m_BackWidget;
    int m_diamond_num=ConfigFile::getInstance().getConfig("diamond_num").toInt();
    int m_gold_coin=ConfigFile::getInstance().getConfig("gold_coin").toInt();
    Snake m_Snake;
    Obstacle m_obstacle;//这个声明顺序要在food上面,因为要传入food
    Food m_Food;
    QString m_food_effect;
    FoodEffect effect;
    bool eatFood=false;
    //暂停之后会调上来这个窗口
    bool m_isPaused=true;
    //
    QString is_throw="no";
    int m_interval=0;       //这个interval会被初始化为配置文件速度,但是在游戏内被更改不会影响到其他
    GameMenu *m_gameMenu;
    int m_curr_level=1;
    QTimer * gameTimer;
    void is_Collision();
    void gameRun();
    void addDifficulty(int add_num);
    void isEat();
    void restart();
    void initMenu();
    void keyPressEvent(QKeyEvent *event);//键盘事件按下

    void paintEvent(QPaintEvent *);//绘图
    bool checkProbability(int x);
    int m_CurrentScore=0;  //当前分数
    int m_highScore= 0;

    void paint_CurrentScore(QPainter & painter);

    void paint_num(QPainter & painter);
    void setDifficulty() ;
    void trigger_food_effects();
    explicit GamePlay(QString map_name,QWidget *parent = nullptr);
    ~GamePlay();
signals:

    void gameWin();
    void gameOver();
    void gameReturn();

public slots:

private:
    int base_speed=ConfigFile::getInstance().getConfig("speed").toInt();
    int more_coin_num= 100;
    int more_diamond_up=-1;
    int more_diamond_down=-1;
    int curr_level;
    int m_dead_time=ConfigFile::getInstance().getConfig("dead_time").toInt();
};

#endif // GAMEPLAY_H

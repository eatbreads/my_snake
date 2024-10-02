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

    Snake m_Snake;
    Obstacle m_obstacle;//这个声明顺序要在food上面,因为要传入food
    Food m_Food;

    bool eatFood=false;
    //暂停之后会调上来这个窗口
    bool m_isPaused=true;
    //
    QString is_throw="no";

    GameMenu *m_gameMenu;

    QTimer * gameTimer;
    void is_Collision();
    void gameRun();

    void isEat();
    void restart();
    void initMenu();
    void keyPressEvent(QKeyEvent *event);//键盘事件按下

    void paintEvent(QPaintEvent *);//绘图

    int m_CurrentScore=0;  //当前分数
    int m_highScore= 0;

    void paint_CurrentScore(QPainter & painter);

    void paint_HighScore(QPainter & painter);
    void setDifficulty() ;
    explicit GamePlay(QWidget *parent = nullptr);
signals:

    void gameWin();
    void gameOver();
    void gameReturn();

public slots:

private:

};

#endif // GAMEPLAY_H

#ifndef SNAKE_H
#define SNAKE_H
#include"mypoint.h"
#include"config.h"
#include <QList>
#include<QObject>
#include<QDebug>
#include "ConfigFile.h"

enum SnakeColor {
    SnakeColor_Red,
    SnakeColor_Green,
    SnakeColor_Black,
    SnakeColor_Yellow
};

class Snake
{
public:


    MyPoint m_Head;//头坐标

    QList<MyPoint>m_Body;//所有坐标

    char m_Direction;//方向 w s a d


    void init();
    void nextSnake();
    void nextSnake_throw();
    void eraseTail();

    bool m_CantCon=false;

    Snake();
    SnakeColor getColorEnum() const;

private:
    QString color="yellow";//颜色
    ConfigFile& m_config=ConfigFile::getInstance();

};

#endif // SNAKE_H

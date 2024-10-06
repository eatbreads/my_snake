#ifndef FOOD_H
#define FOOD_H

#include "mypoint.h"
#include <QList>
#include "config.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <qDebug.h>
#include "ConfigFile.h"
enum FoodEffect {
    Accelerate,       // 加速
    Decelerate,       // 减速
    Other,
    ShrinkTail,       // 尾巴变短
    IncreaseGold,     // 增加金币
    IncreaseDiamond,   // 增加钻石
    FoodEffectNum
};
class Food
{
public:
    MyPoint m_Point; // 当前食物的位置点

    std::vector<std::vector<bool>> arr; // 一个二维布尔向量，用于标记游戏区域中哪些位置已有食物
    std::vector<MyPoint> m_PointArr; // 一个MyPoint向量，用于临时存储可能的食物位置

    int m_EffPointSum = 0; // 有效食物位置的数量
    int eated_food_num = 0;
    int m_food_target= 0;
    bool m_NoFood; // 标记是否没有可用的食物位置

    void giveFood(QList<MyPoint>& v, const std::vector<std::vector<bool>>& Obstacles); // 成员函数，用于在给定的QList<MyPoint>中放置食物，并更新当前食物位置

    Food(const std::vector<std::vector<bool>>& obstacles);
};

#endif // FOOD_H

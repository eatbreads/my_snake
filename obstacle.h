#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "mypoint.h"
#include <QList>
#include "config.h"
#include <ctime>
#include <iostream>
#include <QString>
#include "ConfigFile.h"
#include <QTextStream>
#include <vector>
class Obstacle
{
public:

    std::vector<std::vector<bool>> arr;
    //bool arr[GAME_HEIGHT][GAME_WIDTH]; // 一个二维布尔数组，用于标记游戏区域中哪些位置已有障碍物


    int m_EffPointSum = ConfigFile::getInstance().getConfig("obstacle_num").toInt(); // 有效障碍物位置的数量

    QString is_rand=ConfigFile::getInstance().getConfig("is_rand");

    Obstacle(QString map_name);
    bool hasObstacle(int x,int y);
    void placeObstacleRandomly(); // 随机生成障碍物位置，避免蛇的出生位置和已有障碍物
    void placeObstacleFromVector(QString map_name); // 根据bool数组
    void show();
};

#endif // OBSTACLE_H

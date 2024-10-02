#include "obstacle.h"

Obstacle::Obstacle()
:arr(GAME_HEIGHT, std::vector<bool>(GAME_WIDTH, false))
{
    //memset(arr, 0, sizeof(arr)); // 使用memset初始化arr数组为全0，表示游戏区域开始时都是空的
    //m_NoObstacle = false; // 表示现在没有障碍物短缺
    if(is_rand=="yes")
        placeObstacleRandomly();
    else placeObstacleFromString(ConfigFile::getInstance().getConfig("obstacle_string"));

}

void Obstacle::placeObstacleRandomly()
{
    for(int i = 0; i<m_EffPointSum; i++)
    {
        int tempW=rand()%(GAME_WIDTH);
        int tempH=rand()%(GAME_HEIGHT);
        arr[tempH][tempW]=true;
    }
    //把蛇一开始的位置去掉
    arr[0][3]=false;
    arr[0][2]=false;
    arr[0][1]=false;
    arr[0][0]=false;
}

void Obstacle::placeObstacleFromString(const QString& obstacleString)
{

}

bool Obstacle::hasObstacle(int x,int y)
{
    return arr[x][y];
}

void Obstacle::show()
{
    QTextStream out(stdout); // 使用 QTextStream 以便在 Qt 应用程序中输出
    for (int i = 0; i < GAME_HEIGHT; ++i) {
        for (int j = 0; j < GAME_WIDTH; ++j) {
            out << (arr[i][j] ? "1" : "0") << ",";
        }
        out << "\n"; // 每行结束后换行
    }

    // // 注意这里的循环顺序和索引计算，以实现沿对角线的翻转
    // for (int i = 0; i < GAME_HEIGHT; ++i) { // 这里用GAME_HEIGHT，因为翻转后宽度和高度可能互换
    //     for (int j = 0; j < GAME_WIDTH; ++j) {

    //         out << (arr[GAME_WIDTH-1-j][GAME_HEIGHT-1-i] ? "1" : "0") << ",";
    //     }
    //     out << "\n"; // 每“翻转后的行”结束后换行（注意这里的“翻转后的行”实际上对应于原始数组的列）
    // }
}

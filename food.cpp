#include "food.h"

Food::Food(const std::vector<std::vector<bool>>& obstacles)
    : arr(GAME_HEIGHT, std::vector<bool>(GAME_WIDTH, false)), // 初始化二维向量
    m_PointArr(GAME_WIDTH * GAME_HEIGHT + 10) // 初始化一维向量，尽管这里可能过大，但为了与原始代码一致，暂时保留
{
    m_food_target=ConfigFile::getInstance().getConfig("food_target").toInt();
    srand((unsigned)time(NULL));

    // 增加一点逻辑，在Obstacles为1的位置也不能生成
    bool placed = false;
    while (!placed) {
        int tempW = rand() % (GAME_WIDTH - 2) + 1; // 避免边缘
        int tempH = rand() % (GAME_HEIGHT - 2) + 1; // 避免边缘

        // 检查障碍物
        if (obstacles[tempH][tempW] == 0) {
            m_Point.setPoint(tempW, tempH); // 设置食物位置
            placed = true; // 食物已放置
            m_NoFood = false; // 表示现在没有食物短缺
        }
    }

    // 清理m_PointArr中不必要的元素（实际上，这里可以动态调整大小，但为了与原始逻辑保持一致，先保留）
    m_EffPointSum = 0;
}

void Food::giveFood(QList<MyPoint>& v, const std::vector<std::vector<bool>>& Obstacles)
{
    arr.assign(GAME_HEIGHT, std::vector<bool>(GAME_WIDTH, false)); // 重新初始化二维向量
    m_PointArr.clear();
    // 不在障碍物的位置生成食物，也不在蛇的位置生成食物
    for (auto& it : v)
    {
        arr[it.getY()][it.getX()] = true; // 标记蛇的位置
    }
    MyPoint p;
    int pushCount = 0; // 添加一个计数器来跟踪push的次数
    for (int i = 0; i < GAME_HEIGHT; ++i)
    {
        for (int j = 0; j < GAME_WIDTH; ++j)
        {
            if (!arr[i][j] && !Obstacles[i][j]) // 计算还有多少能放的位置
            {
                p.setPoint(j, i); // 可能的食物位置
                m_PointArr.push_back(p); // 添加到向量中
                ++m_EffPointSum;
                // 打印前十次push进去元素的x和y值
                // if (++pushCount <= 10)
                // {
                //     //qDebug() << "Adding food at x:" << p.getX() << "y:" << p.getY();
                //     //qDebug() << "向量里的为 at x:" << m_PointArr[pushCount-1].getX() << "y:" << m_PointArr[pushCount-1].getY();
                // }
            }
        }
    }
    // 没有能放的位置就返回
    if (m_EffPointSum == 0||eated_food_num>=m_food_target)
    {
        qDebug()<<"e_Eff:"<<m_EffPointSum<<" eated"<<eated_food_num<<" target"<<m_food_target;
        m_NoFood = true;
        return;
    }
    // 随机选择一个能放的位置

    p = m_PointArr[rand() % m_EffPointSum];

    m_PointArr.clear(); // 清理向量
    m_EffPointSum = 0;

    // 这里可以添加额外的调试信息来打印最终选择的食物位置，但之前你已经注释掉了这部分代码
    //qDebug() << "Preparing to generate food at x:" << p.getX() << "y:" << p.getY();
    this->m_Point = p;
}

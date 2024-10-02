#include "food.h"

Food::Food(std::vector<std::vector<bool>>& obstacles)
{
    memset(arr,0,sizeof(arr));// 使用memset初始化arr数组为全0，表示游戏区域开始时都是空的
    srand((unsigned)time(NULL));
    // 随机生成一个在游戏区域内部（避免边缘）的食物位置,这里是是为了不和蛇一起生成
    // int tempW=rand()%(GAME_WIDTH-3)+3;
    // int tempH=rand()%(GAME_HEIGHT-3)+3;
    // m_Point.setPoint(tempW,tempH);//设置食物位置
    // m_NoFood=false;//表示现在没有食物短缺

    // 增加一点逻辑,在Obstacles为1的位置也不能生成
    bool placed = false;
    while (!placed) {
        int tempW = rand() % (GAME_WIDTH - 2) + 1; // 避免边缘，使用1到GAME_WIDTH-2的范围
        int tempH = rand() % (GAME_HEIGHT - 2) + 1; // 避免边缘，使用1到GAME_HEIGHT-2的范围

        // 检查障碍物
        if (obstacles[tempH][tempW]==0) {
            m_Point.setPoint(tempW, tempH); // 设置食物位置
            placed = true; // 食物已放置
            m_NoFood=false;//表示现在没有食物短缺
        }
    }

}
void Food::giveFood(QList<MyPoint> &v,std::vector<std::vector<bool>>& Obstacles)
{
    memset(arr,0,sizeof(arr));
    //不在障碍物的位置生成食物
    for(auto it=v.begin();it!=v.end();++it)//不在蛇的位置生成食物
    {
        arr[it->getY()][it->getX()]=1;//这个蛇是逆过来放的,所以也会适配我的bool
    }
    MyPoint p;
    for(int i=0;i<GAME_HEIGHT;++i)
    {
        for(int j=0;j<GAME_WIDTH;++j)
        {
            if(arr[i][j]==0&&Obstacles[i][j]==0)//计算还有多少能放的位置
            {
                p.setPoint(j,i);//m_PointArr表示可能放的位置
                m_PointArr[this->m_EffPointSum]=p;//表示这边可能放
                ++m_EffPointSum;
            }
        }
    }//没有能放的就返回
    if(m_EffPointSum==0){m_NoFood=true;return;}
    p=m_PointArr[rand()%m_EffPointSum];//随机寻找一个能放的
    MyPoint initP;
    for(auto&val:m_PointArr){val=initP;}
    m_EffPointSum=0;
    this->m_Point=p;
}

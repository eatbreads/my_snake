#include "gameplay.h"

// GamePlay类的构造函数
GamePlay::GamePlay(QString map_name,QWidget *parent) : QWidget(parent),m_obstacle(map_name),m_Food(m_obstacle.arr)
{
    initMenu();

    m_obstacle.show();
    QString lastChar = map_name.right(1); // 获取最后一个字符
    curr_level = lastChar.toInt();
    is_throw=ConfigFile::getInstance().getConfig("is_throw");
    m_highScore=ConfigFile::getInstance().getConfig("highest_score").toInt();
    // 设置窗口标题
    this->setWindowTitle(WINDOW_NAME);
    // 设置窗口的固定大小
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // 创建一个10x10的透明图像，并用作窗口图标
    QImage image(QSize(10,10), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPixmap tempPixmap = QPixmap::fromImage(image);
    this->setWindowIcon(QIcon(tempPixmap));

    // 初始化游戏定时器
    m_interval=ConfigFile::getInstance().getConfig("speed").toInt();
    gameTimer = new QTimer(this);
    gameTimer->start(m_interval); // 设置定时器事件每100毫秒触发一次
    // 延迟500毫秒后连接定时器信号到游戏运行槽,表示500毫秒之后计时器开始运行
    QTimer::singleShot(500, this, [=](){
        connect(gameTimer, &QTimer::timeout, this,[=](){
            if(m_isPaused==false)
                gameRun(); // 定时器触发时调用游戏运行函数
        });
    });

    // 设置窗口不接收焦点
    setFocusPolicy(Qt::NoFocus);
}
GamePlay::~GamePlay()
{
    ConfigFile& instance= ConfigFile::getInstance();
    instance.setConfig("highest_score",QString::number(m_highScore));
    instance.setConfig("diamond_num",QString::number(m_diamond_num));
    instance.setConfig("gold_coin",QString::number(m_gold_coin));
    instance.setConfig("dead_time",QString::number(m_dead_time));
    instance.saveConfig("E:\\qt_project\\eat_snake\\my_snake\\config.json");
}
void GamePlay::initMenu()
{
    m_gameMenu = new GameMenu(this);
    m_gameMenu->hide();
    //接收menu的信号
    connect(m_gameMenu, &GameMenu::gameResume,this, [=](){
        m_gameMenu->hide();
        this->setFocus();
        m_isPaused = false;
    });

    connect(m_gameMenu, &GameMenu::gameSave,this, [=](){

        m_gameMenu->hide();

    });

    connect(m_gameMenu, &GameMenu::gameReturn,this, [=](){
        m_isPaused=true;
        m_gameMenu->hide();
        emit gameReturn();
    });
}
void GamePlay::restart()
{
    qDebug()<<"restart";
    m_CurrentScore = 0;
    // m_isPaused=false;
    is_throw=ConfigFile::getInstance().getConfig("is_throw");
    if(ConfigFile::getInstance().getConfig("more_gold")=="yes")
        more_coin_num=150;
    if(ConfigFile::getInstance().getConfig("more_diamond")=="yes")
    {
        more_diamond_down=151;
        more_diamond_up=170;
    }
    m_Snake.init();
    m_isPaused=false;
}
// 游戏主运行函数
void GamePlay::gameRun()
{
    if(is_throw=="no")m_Snake.nextSnake(); // 蛇的下一步移动
    else m_Snake.nextSnake_throw();

    isEat(); // 检查是否吃到食物
    is_Collision();
    if (!this->eatFood)
    {
        m_Snake.eraseTail(); // 没有吃到食物则删除蛇尾
    }
    else trigger_food_effects();
    this->eatFood = false; // 重置吃到食物的标志

    update(); // 重绘界面
    //qDebug()<<m_Snake.m_CantCon;
    // 检查游戏是否结束
    if (m_Snake.m_CantCon)
    {
        if(m_CurrentScore>m_highScore)
        {
            m_highScore = m_CurrentScore;
        }
        m_dead_time++;
        m_isPaused = true;//暂时用这个,不然一直进去
        emit gameOver(); // 发射游戏结束信号
    }
    // 检查是否吃完所有食物,或者已经达到目标
    if (m_Food.m_NoFood)
    {
        if(m_CurrentScore>m_highScore)
        {
            m_highScore = m_CurrentScore;
        }
        m_isPaused = true;//暂时用这个,不然一直进去
        emit gameWin(); // 发射游戏胜利信号
    }
}

// 检查蛇是否吃到食物
void GamePlay::isEat()
{
    if (m_Snake.m_Head == m_Food.m_Point)
    {
        this->eatFood = true;
        this->m_CurrentScore ++;
        m_Food.eated_food_num++;
        m_Food.giveFood(m_Snake.m_Body,m_obstacle.arr); // 生成新的食物
    }
}

void GamePlay::is_Collision()
{
    int x = m_Snake.m_Head.getY();
    int y = m_Snake.m_Head.getX();
    if(m_obstacle.hasObstacle(x,y))
    {
        m_Snake.m_CantCon=true;
    }
}
// 绘制游戏界面
void GamePlay::paintEvent(QPaintEvent *)
{

    // 设置画笔和画刷
    // QPen pen;
    // pen.setStyle(Qt::NoPen);
    //QBrush brush; brush.setColor(QColor(0,255,0,120));
    //brush.setStyle(Qt::SolidPattern);
    //painter.setPen(pen); painter.setBrush(brush);
    //////////////////////////
    QColor snakeColor;
    switch (m_Snake.getColorEnum())
    {
    case SnakeColor_Red:
        snakeColor = Qt::red;
        break;
    case SnakeColor_Green:
        snakeColor = Qt::green;
        break;
    case SnakeColor_Black:
        snakeColor = Qt::black;
        break;
    case SnakeColor_Yellow:
        snakeColor = Qt::yellow;
        break;
    }

    QPainter painter(this);
    QBrush brush(snakeColor, Qt::SolidPattern);
    painter.setBrush(brush);

    // 不需要设置画笔，因为你不绘制蛇的边框（Qt::NoPen表示没有边框）
    QPen pen;
    pen.setStyle(Qt::NoPen);
    painter.setPen(pen);
    // 绘制蛇的身体
    for (auto it = m_Snake.m_Body.begin(); it != m_Snake.m_Body.end(); ++it)
    {//这个game_step可以理解为游戏的方格长度,或者理解为像素
        painter.drawRect(it->getX()*GAME_STEP, it->getY()*GAME_STEP, GAME_STEP, GAME_STEP);
    }
    // 设置食物的颜色并绘制食物
    brush.setColor(QColor(255,0,0,120));
    painter.setBrush(brush);
    if (!m_Food.m_NoFood)
    {
        painter.drawRect(m_Food.m_Point.getX()*GAME_STEP, m_Food.m_Point.getY()*GAME_STEP, GAME_STEP, GAME_STEP);
    }
    //绘制障碍物
    brush.setColor(QColor(89,50,50,120));
    painter.setBrush(brush);

    for(int i = 0; i< GAME_HEIGHT;i++)
    {
        for(int j = 0; j< GAME_WIDTH;j++)
        {
            if(m_obstacle.hasObstacle(i,j))
            painter.drawRect(j*GAME_STEP, i*GAME_STEP, GAME_STEP, GAME_STEP);
        }//这边x轴是向下的好像,所以要这样设计

    }



    // 设置网格线的颜色并绘制网格
    painter.setPen(QPen(QColor(79,79,79,80)));
    //绘制竖线
    for (int i = 0; i <= GAME_WIDTH; ++i)
    {
        painter.drawLine(i*GAME_STEP, 0, i*GAME_STEP, GAME_HEIGHT*GAME_STEP);
    }
    // 绘制横线
    for (int i = 0; i <= GAME_HEIGHT; ++i)
    {
        painter.drawLine(0, i*GAME_STEP, GAME_WIDTH*GAME_STEP, i*GAME_STEP);
    }

    paint_num(painter);

}

// 处理键盘按键事件
void GamePlay::keyPressEvent(QKeyEvent *event)
{
    // 根据按键改变蛇的移动方向
    switch(event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        if (m_Snake.m_Direction == 's') return;
        m_Snake.m_Direction = 'w';
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if (m_Snake.m_Direction == 'd') return;
        m_Snake.m_Direction = 'a';
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if (m_Snake.m_Direction == 'w') return;
        m_Snake.m_Direction = 's';
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if (m_Snake.m_Direction == 'a') return;
        m_Snake.m_Direction = 'd';
        break;
    case Qt::Key_Space:

        if(m_isPaused==false)
        {
            m_isPaused = true;
            m_gameMenu->show();}
        else
        {
            m_isPaused = false;
            m_gameMenu->hide();
        }
        break;
    default:
        break;
    }
}


void GamePlay::paint_num(QPainter & painter)
{
    //QColor scoreColor(255, 255, 255); // 白色
    QColor scoreColor(0, 0, 0); // 设定为黑色
    QFont scoreFont("Arial", 16, QFont::Bold);
    painter.setPen(QPen(scoreColor));
    painter.setFont(scoreFont);

    // 计算分数表单的位置和大小
    int scoreWidth = 200; // 分数区域的宽度
    int scoreMargin = 30; // 分数区域与游戏窗口之间的边距
    int scoreX = width() - scoreWidth - scoreMargin; // 分数区域的X坐标
    int scoreY = scoreMargin; // 分数区域的Y坐标（可以从顶部开始）
    int lineHeight = 30; // 每行文本的高度

    // 绘制当前分数
    QString currentScoreText = QString("分数: %1").arg(m_CurrentScore);
    painter.drawText(scoreX, scoreY, currentScoreText);
    scoreY += lineHeight;



    QString highScoreText = QString("历史最高分数:%1").arg(m_highScore);
    painter.drawText(scoreX, scoreY, highScoreText);
    scoreY += lineHeight;

    QString String_curr_level = QString("当前为第%1关").arg(curr_level);
    painter.drawText(scoreX, scoreY, String_curr_level);
    scoreY += lineHeight;

    QString temp4 = QString("目标分数为:%1").arg(m_Food.m_food_target);
    painter.drawText(scoreX, scoreY, temp4);
    scoreY += lineHeight;
    QString temp1 = QString("金币数量:%1").arg(m_gold_coin);
    painter.drawText(scoreX, scoreY, temp1);
    scoreY += lineHeight;

    QString temp3 = QString("总共死亡次数为:%1次").arg(m_dead_time);
    painter.drawText(scoreX, scoreY, temp3);
    scoreY += lineHeight;

    QString temp2 = QString("钻石数量:%1").arg(m_diamond_num);
    painter.drawText(scoreX, scoreY, temp2);
    scoreY += lineHeight;

    painter.drawText(scoreX, scoreY, m_food_effect);
    scoreY += lineHeight;

}
void GamePlay::setDifficulty() {

    QString temp = ConfigFile::getInstance().getConfig("difficulty");
    if(temp=="easy") m_interval=100;
    else if(temp =="medium") m_interval=80;
    else if(temp == "hard") m_interval =50;
    else m_interval = 30;
    gameTimer->setInterval(m_interval);
}
void GamePlay::addDifficulty(int add_num) {

    m_interval+=add_num;
    gameTimer->setInterval(m_interval);
}


void GamePlay::trigger_food_effects()
{
    int randomNumber = rand() % 201; // 生成0到100之间的随机数
    // 根据随机数区间设置effect
    if (randomNumber < 10) {
        effect = ShrinkTail;
    } else if (randomNumber <= 70) {
        effect = IncreaseGold;
    } else if (randomNumber <= 80) {
        effect = IncreaseDiamond;
    } else if (randomNumber <= 90) {
        effect = Accelerate;
    } else if (randomNumber <= 100) {
        effect = Decelerate;
    } else if (randomNumber <= more_coin_num)
    {
        effect = IncreaseGold;
    }else if(randomNumber>=more_diamond_down&&randomNumber<=more_diamond_up)
        effect = IncreaseDiamond;
    else {
        effect = Other;
    }
    //effect=ShrinkTail;
    // 根据特效执行相应的操作
    switch (effect) {
    case Accelerate:
        // 实现加速逻辑
        {
            int temp=m_interval/2;
            addDifficulty(-temp);
            m_food_effect="难度升级";
        }
            break;
    case Decelerate:
        // 实现减速逻辑
        {
                int temp=m_interval/3;
                addDifficulty(temp);
                m_food_effect="难度降低";
        }
        break;
    case Other:
        m_food_effect="其他";
        break;
    case ShrinkTail:
        m_food_effect="尾巴变短";
        m_Snake.eraseTail();
        m_Snake.eraseTail();
        break;
    case IncreaseGold:
        m_food_effect="获得一枚金币";
        m_gold_coin++;
        break;
    case IncreaseDiamond:
        m_food_effect="获得一枚钻石";
        m_diamond_num++;
        break;
     default:
         effect=FoodEffectNum;
         m_food_effect="";
         break;
    }
}
bool GamePlay::checkProbability(int x)
{
    if (x <= 0) {
        qDebug() << "Error: x must be greater than 0.";
    }
    int randomNumber = rand() % x;
    // 如果随机数为0，则返回true，否则返回false
    return randomNumber == 0;
}

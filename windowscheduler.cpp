// WindowScheduler.cpp
 #include "WindowScheduler.h"

WindowScheduler::WindowScheduler(QWidget *parent)
    : QObject(parent), currentWindow(nullptr)
{
    initializeWindows();

    // 连接信号和槽
    connect(gameStartWindow, &Widget::startGame, this, &WindowScheduler::handleGameStart);
    connect(gameStartWindow, &Widget::setSkin, this, &WindowScheduler::handleSetSkin);
    connect(gameStartWindow, &Widget::setdif, this, &WindowScheduler::handleSetDif);
    connect(gameStartWindow, &Widget::setSkin, this, &WindowScheduler::handleSetSkin);
    connect(gameStartWindow, &Widget::setObs, this, &WindowScheduler::handleObs);
    connect(gameStartWindow, &Widget::selectLevel, this, &WindowScheduler::handleSelectLevel);
    //这边不用启用,统一使用了重新注册的函数了,因为delete之后会重置他的槽函数
    // connect(gamePlayWindow, &GamePlayWindow::gameTwo, this, &WindowScheduler::handleGameTwo);
    // connect(gamePlayWindow, &GamePlayWindow::gameOnline, this, &WindowScheduler::handleGameOnline);
    // connect(gamePlayWindow, &GamePlay::gameWin, this, &WindowScheduler::handleGameWin);
    // connect(gamePlayWindow, &GamePlay::gameOver, this, &WindowScheduler::handleGameOver);
    // connect(gamePlayWindow, &GamePlay::gameReturn, this, &WindowScheduler::handleReturn);


    // 假设有发射 setSkin 和 setDif 信号的地方，连接它们到相应的槽
    // 例如：connect(someObject, &SomeClass::setSkin, this, &WindowScheduler::handleSetSkin);
    connect(gameEndWindow, &GameEnd::newGame, this, &WindowScheduler::handleGameNew);
    connect(gameWinWindow, &GameEnd::newGame, this, &WindowScheduler::handleGameNext);
    connect(gameDiffWindow,&GameDiffWindow::gameReturn, this, &WindowScheduler::handleReturn);
    connect(gameSkinWindow,&GameSkin::gameReturn, this, &WindowScheduler::handleReturn);

    connect(gameObstacleSetter,&ObstacleSetter::gameReturn, this, &WindowScheduler::handleReturn);
    connect(gameLevelSelector,&LevelSelector::goToPreviousLevel, this, &WindowScheduler::handlePreLevel);
    connect(gameLevelSelector,&LevelSelector::goToNextLevel, this, &WindowScheduler::handleNextLevel);
    connect(gameLevelSelector,&LevelSelector::startGame, this, &WindowScheduler::handleGameNew);

}

WindowScheduler::~WindowScheduler()
{
    ConfigFile& instance= ConfigFile::getInstance();
    instance.setConfig("highest_score",QString::number(gamePlayWindow->m_highScore));
    instance.setConfig("highest_score",QString::number(gamePlayWindow->m_diamond_num));
    instance.setConfig("highest_score",QString::number(gamePlayWindow->m_gold_coin));
    instance.saveConfig("E:\\qt_project\\eat_snake\\my_snake\\config.json");

    // 清理窗口，如果需要的话
    delete gameStartWindow;
    delete gamePlayWindow;
    delete gameEndWindow;
    delete gameSkinWindow;
    delete gameDiffWindow;
    delete gameCompleteWindow;
}

void WindowScheduler::re_register_GamePlayWindow()
{
    Curr_level = ConfigFile::getInstance().getConfig("curr_level");
    if(gamePlayWindow)delete gamePlayWindow;
    //qDebug()<<"开始new";
    gamePlayWindow = new GamePlay(Curr_level);
    //qDebug()<<"结束new";
    connect(gamePlayWindow, &GamePlay::gameWin, this, &WindowScheduler::handleGameWin);
    connect(gamePlayWindow, &GamePlay::gameOver, this, &WindowScheduler::handleGameOver);
    connect(gamePlayWindow, &GamePlay::gameReturn, this, &WindowScheduler::handleReturn);
}
void WindowScheduler::re_register_SelectLevel(int x)//表示前进和后退几关
{
    Curr_level = ConfigFile::getInstance().getConfig("curr_level");
    //这边不需要析构
    //if(gameLevelSelector)delete gameLevelSelector;
    qDebug()<<"开始new";
    int nextlevel= Curr_level.right(1).toInt()+x;


    // 构建新的当前关卡字符串
    // 假设Curr_level的格式是"something_XX"，其中XX是关卡数
    Curr_level = Curr_level.left(Curr_level.length() - 1) +QString::number(nextlevel);
    ConfigFile::getInstance().setConfig("curr_level",Curr_level);
    gameLevelSelector->restart();

}
void WindowScheduler::initializeWindows()
{
    //qDebug()<<"speed:"<<m_configfile.getConfig("speed");

    gameStartWindow = new Widget(); //这边传进去的this是QObject,表示加入对象树而已
    //二更:打算用到了再创建//三更,直接创建即可
    // gamePlayWindow = new GamePlay();//这边逻辑不对,new出来之后定时器就开始了
    gameEndWindow = new GameEnd("GAME OVER,按回车开始",0);
    gameWinWindow = new GameEnd("你赢了,按回车下一关",0);
    gameSkinWindow = new GameSkin();
    gameDiffWindow = new GameDiffWindow(gamePlayWindow);
    gameObstacleSetter = new ObstacleSetter();
    gameLevelSelector = new LevelSelector();
    // 初始化时可以选择显示一个默认窗口，例如游戏开始窗口
    currentWindow = gameStartWindow;

    currentWindow->show();
    currentWindow->setFocus(); // 确保新窗口获得焦点



}

void WindowScheduler::showWindow(QWidget *window)
{
    if (currentWindow)
        currentWindow->hide();

    currentWindow = window;
    currentWindow->show();
    currentWindow->setFocus();
    currentWindow->raise(); // 确保窗口在其他窗口之上
    currentWindow->activateWindow(); // 尝试激活窗口
    currentWindow->setFocus(); // 确保新窗口获得焦点
}

void WindowScheduler::handleGameStart()
{
    qDebug() << "Handling game start";
    //在这边初始化比较合理
    //gamePlayWindow = new GamePlay();
    re_register_GamePlayWindow();
    gamePlayWindow->restart();
    showWindow(gamePlayWindow);
}


void WindowScheduler::handleGameOnline()
{
    qDebug() << "Handling game online";
    // 根据你的逻辑处理在线游戏窗口的显示
    // 例如：showSomeOnlineGameWindow(); 或者重新使用 gamePlayWindow
}
void WindowScheduler::handleReturn()
{
    qDebug() << "Handling Return";
    showWindow(gameStartWindow);

}

void WindowScheduler::handlePreLevel()
{
    qDebug() << "Handling PreLevel";
    if(Curr_level=="obstacle_30*30_map1")return;
    //感觉这个重新注册应该只是调用类里面的重新注册而已,更新一下图片和当前关卡
    re_register_SelectLevel(-1);

    //showWindow(gameLevelSelector);

}
void WindowScheduler::handleNextLevel()
{
    qDebug() << "Handling Next";
    if(Curr_level=="obstacle_30*30_map4")return;
    qDebug()<< "重新注册";
    re_register_SelectLevel(1);
    qDebug()<<"注册结束,启动新窗口";
    showWindow(gameLevelSelector);

}
void WindowScheduler::handleObs()
{
    qDebug() << "Handling Obs";
    showWindow(gameObstacleSetter);
}
void WindowScheduler::handleGameNew()
{
    qDebug() << "Handling game new";
    //新创建一个游戏出来并展示
    re_register_GamePlayWindow();
    gamePlayWindow->restart();
    showWindow(gamePlayWindow);
    //好像这个是不用刷新的,一直存在就行,所以不用delete
    // delete gameEndWindow;
    // gameEndWindow = nullptr;
}
void WindowScheduler::handleSelectLevel()
{
    qDebug() << "Handling selectLevel";
    showWindow(gameLevelSelector);
}
void WindowScheduler::handleGameNext()
{
    qDebug() << "Handling game next";
    //进入下一关游戏
    //更新当前的地图,然后重新载入游戏

    ConfigFile::getInstance().setConfig("curr_level",incrementMapLevel(Curr_level));
    int lastChar=ConfigFile::getInstance().getConfig("curr_level").right(1).toInt();
    if(lastChar>m_level_num)
    {//通关了
        ConfigFile::getInstance().setConfig("curr_level","obstacle_30*30_map1");
        gamePlayWindow->m_isPaused=true;
        show_complete_all_level();
    }
    qDebug()<<ConfigFile::getInstance().getConfig("curr_level");
    re_register_GamePlayWindow();
    gamePlayWindow->restart();
    showWindow(gamePlayWindow);
    //好像这个是不用刷新的,一直存在就行,所以不用delete
    // delete gameEndWindow;
    // gameEndWindow = nullptr;
}


void WindowScheduler::handleGameWin()
{
    qDebug() << "Handling game win";
    showWindow(gameWinWindow); // 显示游戏结束窗口（胜利）
    // delete gamePlayWindow;//这里两行析构还要放在这个show下面,不知道为啥
    // gamePlayWindow = nullptr;//决定不析构了
}

void WindowScheduler::handleGameOver()
{
    qDebug() << "Handling game over";
    showWindow(gameEndWindow); // 显示游戏结束窗口（失败）
    // delete gamePlayWindow;//这里两行析构还要放在这个show下面,不知道为啥
    // gamePlayWindow = nullptr;//决定不析构了
}
void WindowScheduler::handleGameTwo()
{
    qDebug() << "Handling set GameTwe";
    //showWindow(gameDiffWindow); // 显示设置难度窗口
}

void WindowScheduler::handleSetSkin()
{
    qDebug() << "Handling set skin";
    showWindow(gameSkinWindow); // 显示设置皮肤窗口
}

void WindowScheduler::handleSetDif()
{
    qDebug() << "Handling set difficulty";
    showWindow(gameDiffWindow); // 显示设置难度窗口
}


QString WindowScheduler::incrementMapLevel(const QString& curr_level_const) {
    // 使用正则表达式匹配 "map" 后面的数字
    QString curr_level=curr_level_const;
    QRegularExpression re("map(\\d+)");
    QRegularExpressionMatch match = re.match(curr_level);

    if (match.hasMatch()) {
        // 提取数字部分
        QString numberStr = match.captured(1);
        // 将数字部分转换为整数并递增
        bool ok;
        int number = numberStr.toInt(&ok);
        if (ok)
        {
            // 构造新的字符串，将递增后的数字部分替换回去
            QString incrementedPart = QString("map%1").arg(number + 1);
            // 使用 QRegularExpression::replaced 函数替换匹配的部分
            QString new_level = curr_level.replace(match.captured(), incrementedPart);
            return new_level;
        }
    }

    // 如果匹配失败或转换失败，可以返回一个错误消息或原始字符串（这里返回原始字符串）

    qWarning() << "Failed to increment map level in string:" << curr_level;
    return curr_level;
}

void WindowScheduler::show_complete_all_level()
{
    if (!gameCompleteWindow) { // 确保窗口没有被重复创建
        gameCompleteWindow = new QWidget; // 在堆上分配内存，由 WindowScheduler 管理
        gameCompleteWindow->setWindowTitle("恭喜");
        gameCompleteWindow->setGeometry(100, 100, 300, 200); // 设置窗口位置和大小

        QLabel *label = new QLabel("你已经通关全部关卡");
        label->setAlignment(Qt::AlignCenter); // 居中对齐文本

        QVBoxLayout *layout = new QVBoxLayout(gameCompleteWindow); // 注意将 layout 设置为 gameEndWindow 的布局
        layout->addWidget(label);

        gameCompleteWindow->show();
    } else {
        gameCompleteWindow->show(); // 如果窗口已经存在，则只显示它
    }

}

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
    //这边不用启用,统一使用了重新注册的函数了,因为delete之后会重置他的槽函数
    // connect(gamePlayWindow, &GamePlayWindow::gameTwo, this, &WindowScheduler::handleGameTwo);
    // connect(gamePlayWindow, &GamePlayWindow::gameOnline, this, &WindowScheduler::handleGameOnline);
    // connect(gamePlayWindow, &GamePlay::gameWin, this, &WindowScheduler::handleGameWin);
    // connect(gamePlayWindow, &GamePlay::gameOver, this, &WindowScheduler::handleGameOver);
    // connect(gamePlayWindow, &GamePlay::gameReturn, this, &WindowScheduler::handleReturn);


    // 假设有发射 setSkin 和 setDif 信号的地方，连接它们到相应的槽
    // 例如：connect(someObject, &SomeClass::setSkin, this, &WindowScheduler::handleSetSkin);
    connect(gameEndWindow, &GameEnd::newGame, this, &WindowScheduler::handleGameNew);
    connect(gameDiffWindow,&GameDiffWindow::gameReturn, this, &WindowScheduler::handleReturn);
    connect(gameSkinWindow,&GameSkin::gameReturn, this, &WindowScheduler::handleReturn);
}

WindowScheduler::~WindowScheduler()
{
    ConfigFile& instance= ConfigFile::getInstance();
    instance.setConfig("highest_score",QString::number(gamePlayWindow->m_highScore));
    instance.saveConfig("E:\\qt_project\\eat_snake\\my_snake\\config.json");

    // 清理窗口，如果需要的话
    delete gameStartWindow;
    delete gamePlayWindow;
    delete gameEndWindow;
    delete gameSkinWindow;
    delete gameDiffWindow;
}

void WindowScheduler::re_register_GamePlayWindow()
{
    if(gamePlayWindow)delete gamePlayWindow;
    gamePlayWindow = new GamePlay();
    connect(gamePlayWindow, &GamePlay::gameWin, this, &WindowScheduler::handleGameWin);
    connect(gamePlayWindow, &GamePlay::gameOver, this, &WindowScheduler::handleGameOver);
    connect(gamePlayWindow, &GamePlay::gameReturn, this, &WindowScheduler::handleReturn);
}
void WindowScheduler::initializeWindows()
{


    //qDebug()<<"speed:"<<m_configfile.getConfig("speed");

    gameStartWindow = new Widget(); //这边传进去的this是QObject,表示加入对象树而已
    //二更:打算用到了再创建//三更,直接创建即可
    // gamePlayWindow = new GamePlay();//这边逻辑不对,new出来之后定时器就开始了
    gameEndWindow = new GameEnd("GAME OVER,按回车开始",0);
    gameSkinWindow = new GameSkin();
    gameDiffWindow = new GameDiffWindow(gamePlayWindow);

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


void WindowScheduler::handleGameWin()
{
    qDebug() << "Handling game win";
    showWindow(gameEndWindow); // 显示游戏结束窗口（胜利）
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
    qDebug() << "Handling set difficulty";
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

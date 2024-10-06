// WindowScheduler.h
#ifndef WINDOWSCHEDULER_H
#define WINDOWSCHEDULER_H

#include <QObject>
#include <QWidget>
#include <QMap>

// #include "GameStartWindow.h"
// #include "GamePlayWindow.h"
// #include "GameEndWindow.h"
// #include "GameSkinWindow.h"
// #include "GameDiffWindow.h"
#include "widget.h"
#include <QDebug>
#include <QLabel>
#include "gameplay.h"
#include "gameend.h"
#include "gamediffwindow.h"
#include "ConfigFile.h"
#include "gameskin.h"
#include "obstaclesetter.h"
#include "levelselector.h"
class ConfigFile;

class WindowScheduler : public QObject
{
    Q_OBJECT

public:
    explicit WindowScheduler(QWidget *parent = nullptr);
    ~WindowScheduler();

private slots:
    void handleGameStart();
    void handleGameTwo();
    void handleGameOnline();
    void handleGameWin();
    void handleGameOver();
    void handleReturn();
    void handleGameNew();
    void handleSetSkin();
    void handleSetDif();
    void handleGameNext();
    void re_register_GamePlayWindow();
    void re_register_SelectLevel(int x);
    void show_complete_all_level();
    void handleObs();
    void handleSelectLevel();
    void handlePreLevel();
    void handleNextLevel();
private:
    QWidget *currentWindow=nullptr;
    Widget *gameStartWindow=nullptr;
    QWidget *gameCompleteWindow=nullptr; // 通关提示窗口
    GamePlay *gamePlayWindow=nullptr;
    GameEnd *gameEndWindow=nullptr;
    GameEnd *gameWinWindow=nullptr;
    GameSkin *gameSkinWindow=nullptr;
    GameDiffWindow *gameDiffWindow=nullptr;
    ObstacleSetter *gameObstacleSetter=nullptr;
    LevelSelector * gameLevelSelector= nullptr;
    QString Curr_level;
    QString incrementMapLevel(const QString& curr_level);
    void initializeWindows();
    void showWindow(QWidget *window);
    int m_level_num=ConfigFile::getInstance().getConfig("level_num").toInt();
};

#endif // WINDOWSCHEDULER_H

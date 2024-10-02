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
#include "gameplay.h"
#include "gameend.h"
#include "gamediffwindow.h"
#include "ConfigFile.h"
#include "gameskin.h"
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

private:
    QWidget *currentWindow;
    Widget *gameStartWindow;
    GamePlay *gamePlayWindow;
    GameEnd *gameEndWindow;
    GameSkin *gameSkinWindow;
    GameDiffWindow *gameDiffWindow;

    void initializeWindows();
    void showWindow(QWidget *window);
};

#endif // WINDOWSCHEDULER_H

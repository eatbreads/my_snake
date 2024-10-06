#ifndef LEVELSELECTOR_H
#define LEVELSELECTOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QFont>
#include "ConfigFile.h"
#include "config.h"
#include <QFileInfo>
class LevelSelector : public QWidget {
    Q_OBJECT

public:
    explicit LevelSelector(QWidget *parent = nullptr);
    void restart();
private slots:
    void onPreviousLevelButtonClicked();
    void onNextLevelButtonClicked();
    void onStartGameButtonClicked();
signals:
    void goToPreviousLevel();
    void goToNextLevel();
    void startGame();
private:
    void updateScreenshot();
    QLabel *levelLabel;
    QLabel *screenshotLabel;
    QPushButton *previousLevelButton;
    QPushButton *nextLevelButton;
    QPushButton *startGameButton;
    QImage levelScreenshot;
};

#endif // LEVELSELECTOR_H

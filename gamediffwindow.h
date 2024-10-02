#ifndef GAMEDIFFWINDOW_H
#define GAMEDIFFWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include "config.h"
#include "ConfigFile.h"
#include "gameplay.h"
class GamePlay;
class GameDiffWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameDiffWindow(GamePlay * m_gameplay,QWidget *parent = nullptr);

private slots:
    void seteasy();
    void setmedium();
    void sethard();
    void sethell();
    void onBackButtonClicked();
    void onConfirmButtonClicked();

signals:
    void gameReturn();

private:
    void setButtonIcon(QPushButton *button, const QString &imagePath);
    void setbuttonSize(QPushButton* button,int height);
    void showSuccessMessage(const QString &message);
    QPushButton *easyButton;
    QPushButton *mediumButton;
    QPushButton *hardButton;
    QPushButton *hellButton;
    QPushButton *backButton;
    QPushButton *confirmButton;
    GamePlay* m_gamePlay;
};

#endif // GAMEDIFFWINDOW_H

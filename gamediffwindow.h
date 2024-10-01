#ifndef GAMEDIFFWINDOW_H
#define GAMEDIFFWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include "config.h"

class GameDiffWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameDiffWindow(QWidget *parent = nullptr);

private slots:
    void onDifficultyButtonClicked();
    void onBackButtonClicked();
    void onConfirmButtonClicked();

private:
    void setButtonIcon(QPushButton *button, const QString &imagePath);
    void setbuttonSize(QPushButton* button,int height);
    QPushButton *easyButton;
    QPushButton *mediumButton;
    QPushButton *hardButton;
    QPushButton *hellButton;
    QPushButton *backButton;
    QPushButton *confirmButton;
};

#endif // GAMEDIFFWINDOW_H

#ifndef GAMESKIN_H
#define GAMESKIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include "config.h"
#include "ConfigFile.h"
class GameSkin : public QWidget
{
    Q_OBJECT

public:
    explicit GameSkin(QWidget *parent = nullptr);

private slots:
    void setred();
    void setgreen();
    void setblack();
    void setyellow();
    void onBackButtonClicked();
    void onConfirmButtonClicked();
signals:
    void gameReturn();

private:
    void setButtonIcon(QPushButton *button, const QString &imagePath);
    void setbuttonSize(QPushButton* button,int height);
    void showSuccessMessage(const QString &message);
    QPushButton *redButton;
    QPushButton *greenButton;
    QPushButton *blackButton;
    QPushButton *yellowButton;
    QPushButton *backButton;
    QPushButton *confirmButton;
    ConfigFile& m_config=ConfigFile::getInstance();
};

#endif // GAMEDIFFWINDOW_H


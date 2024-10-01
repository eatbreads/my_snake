#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMessageBox>
class GameMenu : public QWidget {
    Q_OBJECT

public:
    GameMenu(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // 创建按钮
        QPushButton *pauseButton = new QPushButton("继续", this);
        QPushButton *saveButton = new QPushButton("存档", this);
        QPushButton *returnButton = new QPushButton("主菜单", this);

        // 将按钮添加到布局
        layout->addWidget(pauseButton);
        layout->addWidget(saveButton);
        layout->addWidget(returnButton);

        // 连接信号和槽
        connect(pauseButton, &QPushButton::clicked, this,[=](){emit gameResume();});
        connect(saveButton, &QPushButton::clicked, this,[=](){emit gameSave();});
        connect(returnButton, &QPushButton::clicked, this,[=](){emit gameReturn();});

        // 设置窗口属性
        this->setWindowTitle("游戏菜单");
        this->setFixedSize(300, 200);
    };

    // void setMainWidget(QWidget *mainWidget) {
    //     m_mainWidget = mainWidget;
    // }
signals:

    void gameResume();
    void gameSave();
    void gameReturn();


private:
         // QWidget *m_mainWidget;
         //SaveGame *m_saveGame;
};
#endif // GAMEMENU_H

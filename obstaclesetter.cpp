// ObstacleSetter.cpp
#include "ObstacleSetter.h"
#include <QMessageBox>

ObstacleSetter::ObstacleSetter(QWidget *parent) : QWidget(parent), rows(WINDOW_HEIGHT / GAME_STEP), cols(WINDOW_WIDTH / GAME_STEP - 100 / GAME_STEP - 2)
{
    // 从配置文件中获取 obstacleMatrix
    obstacleMatrix = ConfigFile::getInstance().getIntMap("obstacle_30*30_map4");

    // 设置窗口标题和大小
    setWindowTitle("Obstacle Setter");
    this->setFixedSize(WINDOW_WIDTH-100, WINDOW_HEIGHT-30);

    // 创建按钮矩阵
    buttonMatrix.resize(rows, std::vector<QPushButton*>(cols));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    for (int i = 0; i < rows; ++i)
    {
        QHBoxLayout *rowLayout = new QHBoxLayout();
        rowLayout->setSpacing(0); // 移除按钮之间的间距
        rowLayout->setContentsMargins(0, 0, 0, 0); // 移除布局边距
        for (int j = 0; j < cols; ++j)
        {
            buttonMatrix[i][j] = new QPushButton("", this);
            buttonMatrix[i][j]->setFixedSize(GAME_STEP, GAME_STEP);

            // 根据 obstacleMatrix 设置按钮的初始颜色
            if (obstacleMatrix[i][j] == 1)
            {
                buttonMatrix[i][j]->setStyleSheet("background-color: gray;");
            }
            else
            {
                buttonMatrix[i][j]->setStyleSheet("background-color: white;");
            }

            // 连接按钮点击信号到槽函数，并传递行列参数
            connect(buttonMatrix[i][j], &QPushButton::clicked, this, [this, i, j]() { onButtonClicked(i, j); });
            rowLayout->addWidget(buttonMatrix[i][j]);
        }
        mainLayout->addLayout(rowLayout);
    }

    // 创建保存按钮
    saveButton = new QPushButton("保存", this);
    saveButton->setFixedSize(100, GAME_STEP); // 保存按钮高度与游戏按钮一致
    connect(saveButton, &QPushButton::clicked, this, &ObstacleSetter::onSaveButtonClicked);

    // 将保存按钮添加到主布局底部，使用 QHBoxLayout 来水平居中
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1); // 添加弹性空间，使保存按钮居中
    buttonLayout->addWidget(saveButton);
    buttonLayout->addStretch(1); // 再次添加弹性空间
    buttonLayout->setContentsMargins(0, 0, 0, 0); // 移除布局边距

    // 将按钮布局添加到主布局的底部
    mainLayout->addLayout(buttonLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0); // 移除布局边距
    setLayout(mainLayout);
}

void ObstacleSetter::onButtonClicked(int row, int col)
{
    // 根据当前按钮颜色设置新颜色
    QString currentStyleSheet = buttonMatrix[row][col]->styleSheet();
    if (currentStyleSheet.contains("gray"))
    {
        buttonMatrix[row][col]->setStyleSheet("background-color: white;");
        obstacleMatrix[row][col] = 0;
    }
    else
    {
        buttonMatrix[row][col]->setStyleSheet("background-color: gray;");
        obstacleMatrix[row][col] = 1;
    }
}

void ObstacleSetter::onSaveButtonClicked()
{
    // 显示保存成功的消息框
    QMessageBox::information(this, "保存成功", "障碍物设置已保存！");
    ConfigFile::getInstance().setMap("obstacle_30*30_map4", obstacleMatrix);
    emit gameReturn();
}

#include "GameSkin.h"

GameSkin::GameSkin(QWidget *parent) : QWidget(parent)
{
    // 设置窗口标题
    setWindowTitle("Game Skin Selector");
    //this->setWindowTitle(WINDOW_NAME);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    QImage image(QSize(10,10),QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPixmap tempPixmap = QPixmap::fromImage(image);
    this->setWindowIcon(QIcon(tempPixmap));
    // 初始化按钮
    redButton = new QPushButton("Red", this);
    greenButton = new QPushButton("Green", this);
    blackButton = new QPushButton("Black", this);
    yellowButton = new QPushButton("Yellow", this);
    backButton = new QPushButton("回退", this);
    confirmButton = new QPushButton("确定", this);

    // 设置按钮图标（假设图标文件存在于项目资源中）
    setButtonIcon(redButton, ":/images/red.png");
    setButtonIcon(greenButton, ":/images/green.png");
    setButtonIcon(blackButton, ":/images/black.png");
    setButtonIcon(yellowButton, ":/images/yellow.png");
    setButtonIcon(backButton, ":/images/back.png"); // 假设有一个返回图标
    setButtonIcon(confirmButton, ":/images/confirm.png"); // 假设有一个确认图标

    // 设置按钮大小
    setbuttonSize(redButton, 150);
    setbuttonSize(greenButton, 150);
    setbuttonSize(blackButton, 150);
    setbuttonSize(yellowButton, 150);
    setbuttonSize(backButton, 150);
    setbuttonSize(confirmButton, 150);

    // 创建布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *colorLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // 添加颜色选择按钮到布局
    colorLayout->addWidget(redButton);
    colorLayout->addWidget(greenButton);
    colorLayout->addWidget(blackButton);
    colorLayout->addWidget(yellowButton);

    // 添加返回和确认按钮到布局
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(confirmButton);

    // 将布局添加到主窗口
    mainLayout->addLayout(colorLayout);
    mainLayout->addStretch(1); // 添加一个弹性空间
    mainLayout->addLayout(buttonLayout);

    // 连接槽函数
    connect(redButton, &QPushButton::clicked, this, &GameSkin::setred);
    connect(greenButton, &QPushButton::clicked, this, &GameSkin::setgreen);
    connect(blackButton, &QPushButton::clicked, this, &GameSkin::setblack);
    connect(yellowButton, &QPushButton::clicked, this, &GameSkin::setyellow);
    connect(backButton, &QPushButton::clicked, this, &GameSkin::onBackButtonClicked);
    connect(confirmButton, &QPushButton::clicked, this, &GameSkin::onConfirmButtonClicked);
}

void GameSkin::setred()
{
    // 设置红色皮肤逻辑（这里只是示例）
    m_config.setConfig("skin_color","red");
    showSuccessMessage("Red skin set!");
}

void GameSkin::setgreen()
{
    // 设置绿色皮肤逻辑
    m_config.setConfig("skin_color","green");
    showSuccessMessage("Green skin set!");
}

void GameSkin::setblack()
{
    // 设置黑色皮肤逻辑
    m_config.setConfig("skin_color","black");
    showSuccessMessage("Black skin set!");
}

void GameSkin::setyellow()
{
    // 设置黄色皮肤逻辑
    m_config.setConfig("skin_color","yellow");
    showSuccessMessage("Yellow skin set!");
}

void GameSkin::onBackButtonClicked()
{
    // 处理返回按钮点击事件（比如关闭窗口或返回上一界面）
    emit gameReturn();
}

void GameSkin::onConfirmButtonClicked()
{
    // 处理确认按钮点击事件（比如保存设置）
    // 这里可以添加保存皮肤设置的逻辑
    showSuccessMessage("Skin settings confirmed!");
    emit gameReturn();
}

void GameSkin::setButtonIcon(QPushButton *button, const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    QIcon icon(pixmap);
    button->setIcon(icon);
    button->setIconSize(pixmap.size());
   // button->setText(""); // 如果有图标，可以移除文本
}

// void GameSkin::setbuttonSize(QPushButton* button, int height)
// {
//     button->setFixedSize(height, height); // 设置按钮的固定大小
// }

void GameSkin::showSuccessMessage(const QString &message)
{
    QMessageBox::information(this, "Success", message);
}


void GameSkin::setbuttonSize(QPushButton* button,int height)
{
    int desiredHeight = height;

    ////////////////////
    QSize buttonSize = button->sizeHint(); // 获取按钮的推荐大小
    buttonSize.setHeight(desiredHeight); // 修改高度为期望值
    button->setMinimumSize(buttonSize); // 设置最小尺寸
    confirmButton->setMinimumSize(buttonSize); // 设置最小尺寸
}

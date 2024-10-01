#include "GameDiffWindow.h"

GameDiffWindow::GameDiffWindow(QWidget *parent) :
    QWidget(parent)
{

    this->setWindowTitle(WINDOW_NAME);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    QImage image(QSize(10,10),QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPixmap tempPixmap = QPixmap::fromImage(image);
    this->setWindowIcon(QIcon(tempPixmap));
    // 假设你在 Qt Designer 中已经布局好了按钮，但这里我们手动添加和布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 难度按钮
    easyButton = new QPushButton("简单", this);
    mediumButton = new QPushButton("中等", this);
    hardButton = new QPushButton("困难", this);
    hellButton = new QPushButton("地狱", this);

    /////////////////

    // 设置按钮图标（假设图片在工作目录下）
    setButtonIcon(easyButton, ":/images/easy.png");
    setButtonIcon(mediumButton, ":/images/medium.png");
    setButtonIcon(hardButton, ":/images/hard.png");
    setButtonIcon(hellButton, ":/images/hell.png");

    // 将难度按钮添加到水平布局中
    QHBoxLayout *difficultyLayout = new QHBoxLayout;
    difficultyLayout->addWidget(easyButton);
    difficultyLayout->addWidget(mediumButton);
    difficultyLayout->addWidget(hardButton);
    difficultyLayout->addWidget(hellButton);

    // 返回和确定按钮
    backButton = new QPushButton("返回", this);
    confirmButton = new QPushButton("确定", this);

    // 设置按钮图标
    setButtonIcon(backButton, ":/images/back.png");
    setButtonIcon(confirmButton, ":/images/confirm.png");

    setbuttonSize(easyButton,300);
    setbuttonSize(mediumButton,300);
    setbuttonSize(hardButton,300);
    setbuttonSize(hellButton,300);

    setbuttonSize(backButton,150);
    // 将返回和确定按钮添加到水平布局中
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch(1);  // 添加间隔
    bottomLayout->addWidget(backButton);
    bottomLayout->addWidget(confirmButton);

    // 将所有布局添加到主布局中
    mainLayout->addLayout(difficultyLayout);
    mainLayout->addStretch(1);  // 添加间隔
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    // 连接信号和槽
    connect(easyButton, &QPushButton::clicked, this, &GameDiffWindow::onDifficultyButtonClicked);
    connect(mediumButton, &QPushButton::clicked, this, &GameDiffWindow::onDifficultyButtonClicked);
    connect(hardButton, &QPushButton::clicked, this, &GameDiffWindow::onDifficultyButtonClicked);
    connect(hellButton, &QPushButton::clicked, this, &GameDiffWindow::onDifficultyButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &GameDiffWindow::onBackButtonClicked);
    connect(confirmButton, &QPushButton::clicked, this, &GameDiffWindow::onConfirmButtonClicked);
}

void GameDiffWindow::setButtonIcon(QPushButton *button, const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        button->setIcon(QIcon(pixmap));
        button->setIconSize(pixmap.size());
        button->setText("");  // 如果只想显示图标，可以隐藏文本
    }
}
void GameDiffWindow::setbuttonSize(QPushButton* button,int height)
{
    int desiredHeight = height;

    ////////////////////
    QSize buttonSize = button->sizeHint(); // 获取按钮的推荐大小
    buttonSize.setHeight(desiredHeight); // 修改高度为期望值
    button->setMinimumSize(buttonSize); // 设置最小尺寸
    confirmButton->setMinimumSize(buttonSize); // 设置最小尺寸
}
void GameDiffWindow::onDifficultyButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        QString difficulty = clickedButton->text();
        // 处理难度选择
    }
}

void GameDiffWindow::onBackButtonClicked()
{
    // 处理返回按钮点击事件
    close();  // 或者执行其他返回操作
}

void GameDiffWindow::onConfirmButtonClicked()
{
    // 处理确定按钮点击事件
}

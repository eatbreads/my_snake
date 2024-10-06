#include "LevelSelector.h"

LevelSelector::LevelSelector(QWidget *parent)
    : QWidget(parent),
    levelLabel(new QLabel(this)),
    screenshotLabel(new QLabel(this)),
    previousLevelButton(new QPushButton("上一关", this)),
    nextLevelButton(new QPushButton("下一关", this)),
    startGameButton(new QPushButton("进入游戏", this)),
    levelScreenshot() // 添加一个成员变量来存储截图（如果需要的话，但这里可能不需要，因为您已经在updateScreenshot中处理了）
{
    // 设置窗口标题和大小
    setWindowTitle("选择关卡");
    setFixedSize(800, 600);

    // 加载关卡截图（动态路径）
    updateScreenshot(); // 这将设置screenshotLabel的pixmap

    // 创建布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 设置关卡编号标签
    int currLevel = ConfigFile::getInstance().getConfig("curr_level").right(1).toInt();
    QString temp4 = QString("第%1关").arg(currLevel);
    levelLabel->setText(temp4);
    levelLabel->setFont(QFont("Arial", 24));
    levelLabel->setAlignment(Qt::AlignCenter);

    // 注意：这里不应该再次尝试从levelScreenshot加载pixmap，因为它在构造函数中是不可见的
    // 而且updateScreenshot已经处理了screenshotLabel的pixmap设置

    // 创建一个水平布局用于放置“进入游戏”按钮和关卡编号标签
    QHBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addStretch(1);
    centerLayout->addWidget(startGameButton, 0, Qt::AlignCenter);
    centerLayout->addStretch(1);

    // 创建水平布局用于放置上一关和下一关按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    previousLevelButton->setFixedSize(150, 50);
    nextLevelButton->setFixedSize(150, 50);
    buttonLayout->addWidget(previousLevelButton);
    buttonLayout->addWidget(nextLevelButton);

    // 创建一个垂直布局用于包裹按钮布局，并添加拉伸因子使其垂直居中
    QVBoxLayout *buttonContainerLayout = new QVBoxLayout();
    buttonContainerLayout->addStretch(1);
    buttonContainerLayout->addLayout(buttonLayout);
    buttonContainerLayout->addStretch(1);

    // 使用一个QWidget作为容器来包裹buttonContainerLayout
    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setLayout(buttonContainerLayout);

    // 创建一个水平布局用于居中对齐 screenshotLabel
    QHBoxLayout *screenshotLayout = new QHBoxLayout();
    screenshotLayout->addStretch(1); // 左侧拉伸因子
    screenshotLayout->addWidget(screenshotLabel); // 添加 screenshotLabel
    screenshotLayout->addStretch(1); // 右侧拉伸因子
    // 将所有控件添加到主布局中
    mainLayout->addWidget(levelLabel);
    mainLayout->addLayout(screenshotLayout); // 使用新的水平布局来添加 screenshotLabel
    mainLayout->addStretch(1);
    mainLayout->addWidget(buttonContainer);
    // 注意：centerLayout 应该被添加到 screenshotLabel 之上或之下，而不是之后，
    // 除非您想要一个特定的垂直顺序。这里我假设您想要它在 screenshotLabel 下面。
    mainLayout->addLayout(centerLayout);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 设置“进入游戏”按钮的字体
    startGameButton->setFont(QFont("Arial", 20));

    // 连接按钮点击信号到对应的槽函数
    connect(previousLevelButton, &QPushButton::clicked, this, &LevelSelector::onPreviousLevelButtonClicked);
    connect(nextLevelButton, &QPushButton::clicked, this, &LevelSelector::onNextLevelButtonClicked);
    connect(startGameButton, &QPushButton::clicked, this, &LevelSelector::onStartGameButtonClicked);

    // 设置布局
    setLayout(mainLayout);

    // 额外的调试信息，检查screenshotLabel的pixmap是否已设置
    qDebug() << "screenshotLabel pixmap set:" << !screenshotLabel->pixmap().isNull();
}

// 更新截图的方法
void LevelSelector::updateScreenshot()
{
    int currLevel = ConfigFile::getInstance().getConfig("curr_level").right(1).toInt();
    QString imagePath = QString("C:\\Users\\18526\\Pictures\\snake_source\\%1.png").arg(currLevel);
    qDebug() << "Loading screenshot for level" << currLevel << "from path:" << imagePath;
    QImage levelScreenshot(imagePath);
    if (!levelScreenshot.isNull()) {
        qDebug() << "Screenshot loaded successfully";
        QPixmap screenshotPixmap = QPixmap::fromImage(levelScreenshot);
        screenshotLabel->setPixmap(screenshotPixmap);
    } else {
        // 如果图片加载失败，可以设置一个默认图片或处理错误
        qDebug() << "Failed to load screenshot, using default";
        QImage defaultImage(QSize(600, 400), QImage::Format_ARGB32);
        defaultImage.fill(Qt::red); // 例如，用红色填充
        QPixmap defaultPixmap = QPixmap::fromImage(defaultImage);
        screenshotLabel->setPixmap(defaultPixmap);
    }
}

// 槽函数实现
void LevelSelector::onPreviousLevelButtonClicked()
{
    emit goToPreviousLevel();
}

void LevelSelector::onNextLevelButtonClicked()
{
    emit goToNextLevel();
}

void LevelSelector::onStartGameButtonClicked()
{
    emit startGame();
}

// restart 函数实现
void LevelSelector::restart()
{
    // 重新加载当前关卡的信息
    int currLevel = ConfigFile::getInstance().getConfig("curr_level").right(1).toInt();
    QString temp4 = QString("第%1关").arg(currLevel);
    levelLabel->setText(temp4);

    // 更新截图
    updateScreenshot();
}

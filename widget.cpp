#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_NAME);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);

    m_GameStartBut=new MyPushButton("游戏开始",200,200*0.618-30,30);
    m_setDifficult=new MyPushButton("设置难度",200,200*0.618-30,30);
    m_setSkin = new MyPushButton("购买皮肤",200,200*0.618-30,30);
    m_setObstacle = new MyPushButton("自定义障碍物",300,200*0.618-30,30);
    m_selectLevel = new MyPushButton("选择关卡",300,200*0.618-30,30);

    m_GameStartBut->setParent(this);
    m_setDifficult->setParent(this);
    m_setObstacle->setParent(this);
    m_setSkin->setParent(this);
    m_selectLevel->setParent(this);

    m_GameStartBut->move((WINDOW_WIDTH-m_GameStartBut->width())*0.5,WINDOW_HEIGHT*0.2);
    m_setObstacle->move((WINDOW_WIDTH-m_GameStartBut->width())*0.5,WINDOW_HEIGHT*0.4);
    m_setDifficult->move((WINDOW_WIDTH-m_GameStartBut->width())*0.5,WINDOW_HEIGHT*0.6);
    m_setSkin->move((WINDOW_WIDTH-m_GameStartBut->width())*0.5,WINDOW_HEIGHT*0.8);
    m_setSkin->move((WINDOW_WIDTH-m_GameStartBut->width())*0.5,WINDOW_HEIGHT*0);



    connect(m_GameStartBut,&MyPushButton::clicked,this,[=](){
        emit startGame();
    });
    connect(m_setDifficult,&MyPushButton::clicked,this,[=](){
         emit setdif();
    });
    connect(m_setSkin,&MyPushButton::clicked,this,[=](){
        emit setSkin();
    });
    connect(m_setObstacle,&MyPushButton::clicked,this,[=](){
        emit setObs();
    });
    connect(m_selectLevel,&MyPushButton::clicked,this,[=](){
        emit selectLevel();
    });
    //这里好像是不用调用show的,因为有父界面,所以会递归调用show
    //m_GameStartBut->hide();//但是可以单独消去一个
    // m_GameStartBut->show();
    // m_setDifficult->show();
    // m_setSkin->show();
}

Widget::~Widget()
{
    delete ui;
}

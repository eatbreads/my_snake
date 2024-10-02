#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mypushbutton.h"
#include "ConfigFile.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    MyPushButton * m_GameStartBut;//开始按钮指针
    MyPushButton * m_setDifficult;
    MyPushButton * m_setSkin;
signals:
    void startGame();
    void setSkin();
    void setdif();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

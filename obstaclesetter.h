// ObstacleSetter.h
#ifndef OBSTACLESETTER_H
#define OBSTACLESETTER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <vector>
#include "config.h"
#include <QSplitter>
#include "ConfigFile.h"
class ObstacleSetter : public QWidget
{
    Q_OBJECT

public:
    explicit ObstacleSetter(QWidget *parent = nullptr);

private slots:
    void onButtonClicked(int row, int col);
    void onSaveButtonClicked();
signals:
    void gameReturn();
private:
    std::vector<std::vector<QPushButton*>> buttonMatrix;
    std::vector<std::vector<int>> obstacleMatrix;
    QPushButton *saveButton;
    int rows, cols;
};

#endif // OBSTACLESETTER_H

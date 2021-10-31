#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QTimer>
#include "../TestUI/ButtonTest.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimeOut();

private:
    void syncToImage();

    QImage* displayImage;
    QLabel* displayLabel;
    QTimer* displayTimer;
    ButtonTest* buttonTest;
};

#endif // MAINWINDOW_H

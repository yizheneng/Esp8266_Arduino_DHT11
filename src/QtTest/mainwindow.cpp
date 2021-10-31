#include "mainwindow.h"
#include "../displayDrivers/DrawOnMemory.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QStyle>
#include <QGridLayout>
uint8_t OLED_GRAM[144][8];     // 页面显示缓存

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    displayImage = new QImage(DRAW_MAX_X + 1, DRAW_MAX_Y + 1, QImage::Format_RGB888);

    displayLabel = new QLabel("picture");
    displayLabel->setPixmap(QPixmap::fromImage(*displayImage));
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(displayLabel);

    upButton = new QPushButton(QApplication::style()->standardIcon((QStyle::StandardPixmap)50), "");
    downButton = new QPushButton(QApplication::style()->standardIcon((QStyle::StandardPixmap)51), "");
    leftButton = new QPushButton(QApplication::style()->standardIcon((QStyle::StandardPixmap)52), "");
    rightButton = new QPushButton(QApplication::style()->standardIcon((QStyle::StandardPixmap)53), "");
    okButton = new QPushButton("OK");

    QGridLayout* btnLayout = new QGridLayout();
    btnLayout->addWidget(upButton, 0, 1);
    btnLayout->addWidget(downButton, 2, 1);
    btnLayout->addWidget(leftButton, 1, 0);
    btnLayout->addWidget(rightButton, 1, 2);
    btnLayout->addWidget(okButton, 1, 1);

    layout->addLayout(btnLayout);

    this->setLayout(layout);

    displayTimer = new QTimer();
    connect(displayTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    displayTimer->start(100);

    buttonTest = new ButtonTest();

    this->setStyleSheet("background-color: #CDC5BF;");
}

MainWindow::~MainWindow()
{
}


void MainWindow::syncToImage()
{
    for(uint8_t i=0;i<8;i++) {
        for(uint8_t n=0;n<128;n++) {
            uint8_t data = OLED_GRAM[n][i];
            for (uint j = 0; j < 8; j ++) {
                if((data >> j & 0x01)) {
                    displayImage->setPixel(n, i * 8 + j, qRgb(255, 255, 255));
                } else {
                    displayImage->setPixel(n, i * 8 + j, qRgb(0, 0, 0));
                }
            }
        }
    }
}

void MainWindow::onTimeOut()
{
    buttonTest->tickOnce();
    buttonTest->event(K_EVENT(K_EVENT_CLASS_TICK_ONCE, 10)); // 滴答信号输入
    syncToImage();
    displayLabel->setPixmap(QPixmap::fromImage(*displayImage));
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
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
    QPushButton* upButton;
    QPushButton* downButton;
    QPushButton* leftButton;
    QPushButton* rightButton;
    QPushButton* okButton;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include "../src/KWidgets/KWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimeOut();

    void onUpBtnClicked();
    void onDownBtnClicked();
    void onLeftBtnClicked();
    void onRightBtnClicked();
    void onOKBtnClicked();

private:
    void syncToImage();

    QImage* displayImage;
    QLabel* displayLabel;
    QTimer* displayTimer;
    KWidget* testUI;
    QPushButton* upButton;
    QPushButton* downButton;
    QPushButton* leftButton;
    QPushButton* rightButton;
    QPushButton* okButton;
};

#endif // MAINWINDOW_H

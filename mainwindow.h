#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camera.h"
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void cam();
    void stop();
    void mic();
    void talk();
    void updatecam(QImage img);
private:
    Ui::MainWindow *ui;
    QThread CameraThread_;
    Camera camera_;
};

#endif // MAINWINDOW_H

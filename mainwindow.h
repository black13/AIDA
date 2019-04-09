#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camera.h"
#include <QThread>
//#include <QTextToSpeech>

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
    void facedetect();
    void updatecam(QImage img);
private:
    Ui::MainWindow *ui;
    QThread CameraThread_;
    Camera camera_;
    //QTextToSpeech m_speech;
};

#endif // MAINWINDOW_H

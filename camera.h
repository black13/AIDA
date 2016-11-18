#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <QObject>
#include <QScopedPointer>
#include <QTimerEvent>
#include <stdio.h>
#include <iostream>
#include <QImage>
#include <QBasicTimer>
//#include <QDebug>
#include <QWidget>

#include <QMessageBox>

class Camera:public QObject{
    Q_OBJECT
    QScopedPointer<cv::VideoCapture> cap;
    QBasicTimer timer_;
    int cameraIndex_;

public:
    //Webcam standard implementare cam diversa
    Camera(int camera_index=0, QObject* parent=0) : QObject(parent)
    {
        cameraIndex_ = camera_index;
    }
    ~Camera();
    void update();
public slots:
    void run();
    void stop();
    QImage MatToQImage(const cv::Mat& mat);
signals:
    void started();
    QImage update(QImage);
private:
    void timerEvent(QTimerEvent * ev);
};
#endif /* !CAMERA_H */

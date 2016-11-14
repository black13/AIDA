#include "camera.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Camera::~Camera()
{
}

void Camera::run()
{
    if (!cap)
    {
        cap.reset(new cv::VideoCapture(cameraIndex_));
    }
    else{
        cap.reset(new cv::VideoCapture(cameraIndex_));
    }

    if (cap->isOpened())
    {
        timer_.start(0, this);
        emit started();
    }


    //QMessageBox messageBox;
    //messageBox.critical(0,"Error","An error has occured !");
    //messageBox.information(0,"Aggiornamenti","Proprietà ancora non disponibile");
}

void Camera::stop()
{
    timer_.stop();
    cap->release();
}

void Camera::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() != timer_.timerId())
        return;
    cv::Mat frame;
    //
     //->setPixmap(QPixmap::fromImage(this->MatToQImage(cv::Mat& frame)));
    if (!cap->read(frame)) // Blocks until a new frame is ready
    {
        timer_.stop();
        return;
    }
    ;
    //MainWindow::MainWindow::updatecam();
    emit update(Camera::MatToQImage(frame));
}

QImage Camera::MatToQImage(const cv::Mat& frame)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(frame.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)frame.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, frame.cols, frame.rows, frame.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    else if(frame.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)frame.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
//        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

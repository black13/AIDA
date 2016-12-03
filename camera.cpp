#include "camera.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Camera::~Camera()
{
}

void Camera::run()
{
    running = 1;
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
}

void Camera::stop()
{
    timer_.stop();
    running = 0;
    cap->release();
}

void Camera::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() != timer_.timerId())
        return;
    cv::Mat frame;
    if (!cap->read(frame)) // Blocks until a new frame is ready
    {
        timer_.stop();
        return;
    }
    ;
    if(facedetect == 0){
                                                 //width,height del label ui->label
    //emit update(Camera::MatToQImage(frame).scaled(451,271,Qt::IgnoreAspectRatio, Qt::FastTransformation ));
    emit update(Camera::MatToQImage(frame).scaled(451,271,Qt::IgnoreAspectRatio, Qt::FastTransformation ));
    }else{
        //Cascade default scelto per il test
        faceCascade.load("../AIDA/resource/cascade/haarcascade_frontalface_default.xml");
        emit update(Camera::facedetector(frame).scaled(451,271,Qt::IgnoreAspectRatio, Qt::FastTransformation ));

    }
}
QImage Camera::facedetector(cv::Mat frame)
{
    cv::Mat grey_image;
    cv::cvtColor(frame, grey_image, CV_BGR2GRAY);
    cv::equalizeHist(grey_image, grey_image);

    std::vector<cv::Rect> faces;
    // Calculate the camera size and set the size to 1/8 of screen height
    faceCascade.detectMultiScale(grey_image, faces, 1.1, 2,  0|CV_HAAR_SCALE_IMAGE,
                                 cv::Size(frame.cols/4, frame.rows/4)); // Minimum size of obj
    //-- Draw rectangles around faces
    for( size_t i = 0; i < faces.size(); i++)
    {
        cv::rectangle(frame, faces[i], cv::Scalar( 255, 0, 255 ));

    }
    /*
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    const QImage image((const unsigned char*)frame.data, frame.cols, frame.rows, frame.step,
                       QImage::Format_RGB888);

    image.rgbSwapped();
    Q_ASSERT(image.constBits() == frame.data);
    return image;
    */
    return Camera::MatToQImage(frame);
}

QImage Camera::MatToQImage(cv::Mat frame)
{
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    const QImage img((const unsigned char*)frame.data, frame.cols, frame.rows, frame.step,
                       QImage::Format_RGB888);
    img.rgbSwapped();
    Q_ASSERT(img.constBits() == frame.data);
    return img;
}


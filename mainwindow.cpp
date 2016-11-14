#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QLabel"
#include "QPixmap"
#include "iostream"

//auto camera_ = new Camera();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this, SLOT(cam()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(stop()));
    camera_.connect(&camera_,SIGNAL(update(QImage)),this,SLOT(updatecam(QImage)));
    //ui->label->pixmap("sami.jpg"); 
    //ui->label->setPixmap(QPixmap(QString::fromUtf8("/home/codematrix/webcam/sami.jpg")));
}
void MainWindow::cam(){
    //Bisogno di un thread
    camera_.run();
    //Thread non workano da controllare piu avanti
    //CameraThread_.start();
    //camera_.moveToThread(&CameraThread_);
}
void MainWindow::updatecam(QImage img){
    ui->label->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::stop(){
   camera_.stop();
   //Pulisco il label
   ui->label->clear();
   //CameraThread_.quit();
   //CameraThread_.wait();
}

MainWindow::~MainWindow()
{
    camera_.~Camera();
    //CameraThread_.quit();
    //CameraThread_.wait();
    delete ui;
}

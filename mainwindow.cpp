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

    //Signal and Slot
    connect(ui->pushButton,SIGNAL(clicked(bool)),this, SLOT(cam()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(stop()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(mic()));
    camera_.connect(&camera_,SIGNAL(update(QImage)),this,SLOT(updatecam(QImage)));


    //Settings
    //Label background nero con bordo nero
    ui->label->setStyleSheet( "border: 1px solid #0000FF; background-color: black; border-radius: 150px;" );
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
void MainWindow::mic(){
    QMessageBox messageBox;
    //messageBox.critical(0,"Error","An error has occured !");
    messageBox.information(0,"In Develop","Feature in developing");
}
MainWindow::~MainWindow()
{
    camera_.~Camera();
    //CameraThread_.quit();
    //CameraThread_.wait();
    delete ui;
}

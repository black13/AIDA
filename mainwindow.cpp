#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QLabel"
#include "QPixmap"
#include "iostream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Signal and Slot
    connect(ui->cam_button,SIGNAL(clicked(bool)),this, SLOT(cam()));
    connect(ui->stopcam_button,SIGNAL(clicked(bool)),this,SLOT(stop()));
    connect(ui->mic_button,SIGNAL(clicked(bool)),this,SLOT(mic()));
    //connect(ui->talk_button,SIGNAL(clicked(bool)),this,SLOT(talk()));
    connect(ui->facedetect_button,SIGNAL(clicked(bool)),this,SLOT(facedetect()));
    camera_.connect(&camera_,SIGNAL(update(QImage)),this,SLOT(updatecam(QImage)));
    //m_speech.setVolume(100.0);
    //Settings
    //Label background nero con bordo nero
    ui->camview_label->setStyleSheet( "border: 1px solid #0000FF; background-color: black; border-radius: 150px;" );
}
void MainWindow::cam(){
    if(camera_.running == 0)
        camera_.run();
    //Thread non workano da controllare piu avanti
    //CameraThread_.start();
    //camera_.moveToThread(&CameraThread_);
}
void MainWindow::updatecam(QImage img){
    ui->camview_label->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::stop(){
   if (camera_.running){
    camera_.stop();
   }
   //Pulisco il label
   ui->camview_label->clear();
   //CameraThread_.quit();
   //CameraThread_.wait();
}
void MainWindow::mic(){
    QMessageBox messageBox;
    //messageBox.critical(0,"Error","An error has occured !");
    messageBox.information(0,"In Develop","Feature in developing");
}
void MainWindow::talk(){
    
//    QString = ui->talk_line.getline();
    if(ui->talk_line->text() == ""){
        QMessageBox messageBox;
        messageBox.information(0,"Error","Impossibile usare talk se talk_line e vuoto");        
    }else{
      //m_speech.say(ui->talk_line->text());        
    }


}
void MainWindow::facedetect(){
    if(camera_.running){
        if(camera_.facedetect == 1){
            camera_.facedetect = 0;
        }
        else{
            camera_.facedetect = 1;
        }
    }
}
MainWindow::~MainWindow()
{
    camera_.~Camera();
    //CameraThread_.quit();
    //CameraThread_.wait();
    delete ui;
}

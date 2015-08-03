#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000/30);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(loop()));
    OpenCamre();
    // eage_detection();
}
void MainWindow::loop(){
    eage_detection();
}
void MainWindow::rotate(Mat &src, double angle, Mat &dst){
        int len = std::max(src.cols, src.rows);
        cv::Point2f pt(len/2., len/2.);
        cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
        cv::warpAffine(src, dst, r, cv::Size(len, len));
}
double MainWindow::size(Mat img){
    int x1,x2;
    for(int i = 0;i<img.cols/2;i++)
    {
       x1++;
    }
    for(int j = img.cols/2;j<img.cols;j++)
    {
        x1++;
    }
    qDebug()<<x1;
    return x1;
}

void MainWindow::eage_detection(){
    Mat src = frame_update();
    Mat show,realCam,tempImage;
    src.copyTo(show);
    size(src);
    src.copyTo(realCam);

    Mat gray,edge,draw;
   // Mat rot_mat( 2, 3, CV_32FC1 );
    Rect bounding_rect;
    cvtColor(src,gray,CV_RGB2GRAY);
   medianBlur( gray, gray, 5);
    threshold(gray,gray,130,255,CV_THRESH_BINARY);
    //Canny(gray,gray,th1,th2,3);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345);
    findContours( gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    edge.convertTo(draw,CV_8U);
    Mat drawing = Mat::zeros( gray.size(), CV_8UC3 );
       for( int i = 0; i< contours.size(); i++ )
       {
           counter++;
          Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
           drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
           bounding_rect = boundingRect(contours[i]);
           rectangle(drawing, bounding_rect, Scalar(255),2, 8,0);
           src = image(bounding_rect);
       }
         ui->label_4->setText(QString::number(contours.size()));
         counter = 0;
         src.copyTo(tempImage);
          //line( tempImage, Point(0,tempImage.cols/2), Point(tempImage.rows,tempImage.cols/2), Scalar(255,0,0), 3, CV_AA);
         cvtColor(src,src,CV_RGB2GRAY);
           threshold(src,src,140,255,CV_THRESH_BINARY);
         Canny(src, src, 50, 200, 3);
         src.copyTo(show);
         vector<Vec2f> lines;
         HoughLines(src, lines, 1, CV_PI/180, 80, 0, 0 );
         double maxline = 0,theta1;
         int index;
         for( size_t i = 0; i < lines.size(); i++ )
         {
              float rho = lines[i][0], theta = lines[i][1];
              Point pt1, pt2;
              double a = cos(theta), b = sin(theta);
              double x0 = a*rho, y0 = b*rho;
              pt1.x = cvRound(x0 + 1000*(-b));
              pt1.y = cvRound(y0 + 1000*(a));
              pt2.x = cvRound(x0 - 1000*(-b));
              pt2.y = cvRound(y0 - 1000*(a));
             line( show, pt1, pt2, Scalar(255), 3, CV_AA);
             double res = cv::norm(pt2-pt1);
             if(maxline < res){
                theta1 = theta/0.01745329252;
             }
         }

      double degree = 90 - theta1;
      //theta1 = degree + theta1;
     // qDebug()<<theta1;
     rotate(show,theta1,show);
     maxline = 0;
     theta1 = 0;
     cv::resize(show,show,cv::Size(280,177));
     cv::resize(tempImage,tempImage,cv::Size(280,177));
     cv::resize(gray,gray,cv::Size(280,177));
     qimage = QImage((const unsigned char*) show.data, show.cols, show.rows, QImage::Format_Indexed8);
     ui->label_3->setPixmap(QPixmap::fromImage(qimage));
     qimage = QImage((const unsigned char*) tempImage.data, tempImage.cols, tempImage.rows, QImage::Format_RGB888);
     ui->label_2->setPixmap(QPixmap::fromImage(qimage));
     qimage = QImage((const unsigned char*) drawing.data, drawing.cols, drawing.rows, QImage::Format_RGB888);
     ui->label->setPixmap(QPixmap::fromImage(qimage));

}

Mat MainWindow::diff_image(Mat bg,Mat img){

return img;
}

Mat MainWindow::frame_update(){
    cap>>image;
    cv::resize(image,image,cv::Size(CAMERA_WIDTH,CAMERA_HEIGHT));
    cvtColor(image,image,COLOR_BGR2RGB);
    return image;
}

void MainWindow::OpenCamre(){
       //----- Open Camera -----//
        cap.open(-1);
        if(cap.isOpened() == false){
            return ;
        }
       // ----- Setting Camera Property -----//
        cap.set(CV_CAP_PROP_FRAME_HEIGHT,760);
        cap.set(CV_CAP_PROP_FRAME_WIDTH,480);
        qDebug()<<"Camera is Opened.";
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    th1 = value;
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
     th2 = value;
}

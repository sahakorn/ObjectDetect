#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QtCore>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void OpenCamre();
    Mat frame_update();
    Mat diff_image(Mat bg,Mat img);
    void eage_detection();
    void rotate(Mat& src , double angle,Mat& dst);
    double size(Mat img);
public slots:
    void loop();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    VideoCapture cap;
    Mat image;
    QImage qimage;
    QTimer* timer;
    Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;
    int CAMERA_WIDTH = 760;
    int CAMERA_HEIGHT = 480;
    int counter;
    int th1,th2;

};

#endif // MAINWINDOW_H

#ifndef CHANNEL_H
#define CHANNEL_H

#include <QWidget>
#include <QSlider>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Channel : public QWidget
{
    Q_OBJECT
public:
    explicit Channel(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1, 1, CV_8UC3));
    QSlider *blue, *green, *red, *contrast, *brightness;
    Mat channelDone() {return dst.clone();}

private:
    Mat src, dst;
    int rows, cols;
    int beta;
    float alpha = 1.00, alpha_b = 1.00, alpha_g = 1.00, alpha_r = 1.00;

private slots:
    void valueChanged(int);
    void rejected();
};

#endif // CHANNEL_H

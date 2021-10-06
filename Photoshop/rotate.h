#ifndef ROTATE_H
#define ROTATE_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Rotate : public QWidget
{
    Q_OBJECT
public:
    explicit Rotate(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1 ,1, CV_8UC3));
    QPushButton *vertical, *horizontal, *clockwise, *counterclockwise;
    Mat rotateFinish() {return dst.clone();}

private:
    Mat src, dst;

private slots:
    void buttonDown();
    void rejected();
};

#endif // ROTATE_H

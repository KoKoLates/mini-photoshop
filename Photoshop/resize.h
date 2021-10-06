#ifndef RESIZE_H
#define RESIZE_H

#include <QWidget>
#include <QSlider>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Resize : public QWidget
{
    Q_OBJECT
public:
    explicit Resize(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1 ,1, CV_8UC3));
    QSlider *sizeSlider;
    Mat sizeFinish()
    {
        dst = temp.clone();
        return dst.clone();
    }

private:
    Mat src, dst, temp;

private slots:
    void valueChanged(int);
    void rejected();
};

#endif // RESIZE_H

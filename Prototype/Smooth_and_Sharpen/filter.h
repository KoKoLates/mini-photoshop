#ifndef FILTER_H
#define FILTER_H

#include <QWidget>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Filter : public QWidget
{
    Q_OBJECT
public:
    explicit Filter(QWidget *parent = nullptr, Mat image = Mat::zeros(1, 1, CV_8U));

    void filter();
    QRadioButton *Box, *Gaussian, *Median, *Bilateral;
    Mat blurDone() {return dst;}

private:
    Mat src, dst;
    int filterIndex, KernelSize;

signals:

private slots:
    void filterChanged();
    void kernelChanged(int);

};

#endif // FILTER_H

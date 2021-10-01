#ifndef BLUR_H
#define BLUR_H

#include <QWidget>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Blur : public QWidget
{
    Q_OBJECT
public:
    explicit Blur(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1, 1, CV_8UC3));
    enum Type {box, gaussian, median, bilateral};
    QRadioButton *Box, *Gaussian, *Median, *Bilateral;
    Mat smoothDone() {return dst;}

private:
    Mat src, dst;
    Blur::Type type;
    int kernel;
    void smooth();

private slots:
    void TypeChanged();
    void kernelChanged(int);
    void rejected();
};

#endif // BLUR_H

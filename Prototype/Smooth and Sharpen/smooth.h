#ifndef SMOOTH_H
#define SMOOTH_H

#include <QWidget>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Smooth : public QWidget
{
    Q_OBJECT
public:
    explicit Smooth(QWidget *parent = nullptr, Mat image = Mat::zeros(1, 1, CV_8U));
    enum Type {box, gaussian, median, bilateral};
    QRadioButton *Box, *Gaussian, *Median, *Bilateral;
    Mat smoothDone() {return dst;}

private:
    Mat src, dst;
    Smooth::Type type;
    int kernel;
    void smooth();

private slots:
    void TypeChanged();
    void kernelChanged(int);

};

#endif // SMOOTH_H

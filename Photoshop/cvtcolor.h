#ifndef CVTCOLOR_H
#define CVTCOLOR_H

#include <QWidget>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class CvtColor : public QWidget
{
    Q_OBJECT
public:
    explicit CvtColor(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1 ,1, CV_8UC3));
    enum Type{GRAY, HSV, HSL, YCRCB};
    QRadioButton *gray, *hsv, *hsl, *ycrcb;
    void color();
    Mat cvtFinish() {return dst.clone();}

private:
    Mat src, dst;
    CvtColor::Type type;

private slots:
    void TypeChanged();
    void rejected();
};

#endif // CVTCOLOR_H

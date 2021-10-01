#ifndef COLORSPACE_H
#define COLORSPACE_H

#include <QWidget>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class ColorSpace : public QWidget
{
    Q_OBJECT
public:
    explicit ColorSpace(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1, 1, CV_8UC3));
    enum Type{GRAY, HSV, HSL, YCRCB};
    QRadioButton *gray, *hsv, *hsl, *ycrcb;
    void color();
    Mat colorMDone() {return dst;}

private:
    Mat src, dst;
    ColorSpace::Type type, pastType;

private slots:
    void TypeChanged();
    void rejected();
};

#endif // COLORSPACE_H

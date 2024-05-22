#ifndef SPECIAL_H
#define SPECIAL_H

#include <QWidget>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class Special : public QWidget
{
    Q_OBJECT
public:
    explicit Special(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1 ,1, CV_8UC3));
    enum Type{DARK, LIGHT, DIAGONAL, ENGRAVING, LIGHTENING, NOISE, SIDE, VIGNETTING};
    QRadioButton *dark, *light, *diagonal, *enrgaving, *lightening, *noise, *side, *vignetting;
    void filter();
    Mat specialFinish() {return dst.clone();}
    double getDistanceFromCorner(const cv::Size &imgSize, const cv::Point &center);

private:
    Mat src, dst;
    int rows, cols;
    Special::Type type;

private slots:
    void TypeChanged();
    void rejected();

};

#endif // SPECIAL_H

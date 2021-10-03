#ifndef CROP_H
#define CROP_H

#include <QWidget>
#include <QVector>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Crop : public QWidget
{
    Q_OBJECT
public:
    explicit Crop(QWidget *parent = nullptr, const Mat& image = Mat::zeros(1, 1, CV_8UC3));
    static void mouseCallback(int, int, int, int, void*);
    QRadioButton *self, *rectangle;
    Mat cropDone() {return dst.clone();}
    enum Type { RECTANGLE, SELF};
    Mat crop(Mat);

private:
    Mat src, dst;
    Crop::Type type;
    Rect2d roi;
    QVector<Point2f>point;

private slots:
    void self1();
    void rectangle1();
    void rejected();
};

#endif // CROP_H

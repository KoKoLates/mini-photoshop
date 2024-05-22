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
    explicit Crop(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1 ,1, CV_8UC3));
    static void onMouseSelf(int, int, int, int, void*);
    static void onMouseRect(int, int, int, int, void*);
    QRadioButton *self, *rectangle;
    Mat cropFinish()
    {
        dst.copyTo(dst);
        return dst;
    }

private:
    Mat src, dst;
    QVector<Point2f>point;
    Point2f s, d;

private slots:
    void TypeChanged();
    void rejected();

};

#endif // CROP_H

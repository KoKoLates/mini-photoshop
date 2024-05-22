#ifndef COLOR_H
#define COLOR_H

#include <QWidget>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Color : public QWidget
{
    Q_OBJECT
public:
    explicit Color(QWidget *parent = nullptr, const Mat &image = Mat::zeros(1 ,1, CV_8UC3));
    enum Type{ RED, BLUE, GREEN, CASTING, COMIC, FROZEN, REVERSE, VINYAGE};
    QRadioButton *red, *blue, *green, *casting, *comic, *frozen, *reverse, *vintage;
    void filter();
    Mat colorFinish() {return dst.clone();}

private:
    Mat src, dst;
    int rows, cols;
    Color::Type type;

private slots:
    void TypeChanged();
    void rejected();

};

#endif // COLOR_H

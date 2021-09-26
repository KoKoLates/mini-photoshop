#ifndef SHARPEN_H
#define SHARPEN_H

#include <QWidget>
#include <QSlider>
#include <QRadioButton>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Sharpen : public QWidget
{
    Q_OBJECT
public:
    explicit Sharpen(QWidget *parent = nullptr, Mat image = Mat::zeros(1, 1, CV_8U));
    enum Type {general, laplacian};
    QRadioButton *General, *Laplacian;
    QSlider *generalSlider, *laplacianSlider;
    Mat sharpenDone() {return dst;}

private:
    Mat src, dst ,copy;
    Sharpen::Type type;
    float weight;

private slots:
    void TypeChanged();
    void valueChanged(int);

};

#endif // SHARPEN_H

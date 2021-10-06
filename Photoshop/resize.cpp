#include "resize.h"

Resize::Resize(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
    dst = temp = src.clone();
}

void Resize::valueChanged(int value)
{
    float percentage = (value + 20.0) / 20.0;
    int width = src.cols * percentage;
    int height = src.rows * percentage;
    cv::resize(src, temp, Size(width,height));
    imshow("Preview", temp);
}

void Resize::rejected()
{
    sizeSlider->setValue(0);
}

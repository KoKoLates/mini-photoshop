#include "smooth.h"

Smooth::Smooth(QWidget *parent, Mat image) : QWidget(parent)
{
    src = image;
    kernel = 1;
}

void Smooth::TypeChanged()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == Box) type = box;
    else if(button == Gaussian) type = gaussian;
    else if(button == Median) type = median;
    else if(button == Bilateral) type = bilateral;
    smooth();
}

void Smooth::kernelChanged(int value)
{
    kernel = value;
    smooth();
}

void Smooth::smooth()
{
    switch (type) {
    case Smooth::box:
        blur(src, dst, Size(kernel,kernel));
        break;

    case Smooth::gaussian:
        GaussianBlur(src, dst, Size(kernel,kernel), 0, 0);
        break;

    case Smooth::median:
        medianBlur(src, dst, kernel);
        break;

    case Smooth::bilateral:
        bilateralFilter(src, dst, 5, kernel * 10, kernel * 10);
        break;

    default:
        dst = src.clone();
    }
    imshow("Preview", dst);
}

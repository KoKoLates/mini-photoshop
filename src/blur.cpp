#include "blur.h"

Blur::Blur(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
    dst = src.clone();
    kernel = 1;
}

void Blur::TypeChanged()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == Box) type = box;
    else if(button == Gaussian) type = gaussian;
    else if(button == Median) type = median;
    else if(button == Bilateral) type = bilateral;
    bluring();
}

void Blur::kernelChanged(int value)
{
    kernel = value;
    bluring();
}

void Blur::bluring()
{
    switch (type) {
    case Blur::box:
        cv::blur(src, dst, Size(kernel,kernel));
        break;

    case Blur::gaussian:
        GaussianBlur(src, dst, Size(kernel,kernel), 0, 0);
        break;

    case Blur::median:
        medianBlur(src, dst, kernel);
        break;

    case Blur::bilateral:
        bilateralFilter(src, dst, 5, kernel * 10, kernel * 10);
        break;

    default:
        dst = src.clone();
    }
    imshow("Preview", dst);
}

void Blur::rejected()
{
    switch (type) {
    case Blur::box:
        Box->setAutoExclusive(false);
        Box->setChecked(false);
        Box->setAutoExclusive(true);
        break;

    case Blur::gaussian:
        Gaussian->setAutoExclusive(false);
        Gaussian->setChecked(false);
        Gaussian->setAutoExclusive(true);
        break;

    case Blur::median:
        Median->setAutoExclusive(false);
        Median->setChecked(false);
        Median->setAutoExclusive(true);
        break;

    case Blur::bilateral:
        Bilateral->setAutoExclusive(false);
        Bilateral->setChecked(false);
        Bilateral->setAutoExclusive(true);
        break;

    default:
        return;
    }
}

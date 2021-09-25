#include "filter.h"

Filter::Filter(QWidget *parent, Mat image) : QWidget(parent)
{
    src = image;
    filterIndex = 0, KernelSize = 1;
}

void Filter::filterChanged()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == Box) filterIndex = 1;
    else if(button == Gaussian) filterIndex = 2;
    else if(button == Median) filterIndex = 3;
    else if(button == Bilateral) filterIndex = 4;
    else filterIndex = 0;

    filter();
}

void Filter::kernelChanged(int value)
{
    KernelSize = value;

    filter();
}

void Filter::filter()
{
    switch (filterIndex) {
    case 1:
        blur(src, dst, Size(KernelSize,KernelSize));
        break;

    case 2:
        GaussianBlur(src, dst, Size(KernelSize,KernelSize), 0, 0);
        break;

    case 3:
        medianBlur(src, dst, KernelSize);
        break;

    case 4:
        bilateralFilter(src, dst, 5, KernelSize * 10, KernelSize * 10);
        break;

    default:
        dst = src.clone();
    }

    imshow("Preview", dst);
}

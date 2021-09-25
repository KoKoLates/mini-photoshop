#include "sharpen.h"

#include <QDebug>

Sharpen::Sharpen(QWidget *parent, Mat image) : QWidget(parent)
{
    src = image;
    dst = src.clone();
}

void Sharpen::TypeChanged()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == General)
    {
        type = general;
        generalSlider->setEnabled(true);
        laplacianSlider->setDisabled(true);
        laplacianSlider->setValue(0);
    }
    else
    {
        type = laplacian;
        generalSlider->setDisabled(true);
        laplacianSlider->setEnabled(true);
        generalSlider->setValue(0);
    }
    imshow("Preview", dst);

    GaussianBlur(src, dst, Size(0,0), 100, 0);
}

void Sharpen::valueChanged(int value)
{
    weight = -(value/50.0);
    addWeighted(src, 1 - weight, dst, weight, 0, dst);
    imshow("Preview", dst);
}


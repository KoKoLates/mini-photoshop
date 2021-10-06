#include "sharpen.h"

Sharpen::Sharpen(QWidget *parent, const Mat &image) : QWidget(parent)
{
    weight = 0.0;
    src = image;
    dst = src.clone();
    src.convertTo(copy,CV_32F);
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
}

void Sharpen::valueChanged(int value)
{
    switch(type){
    case Sharpen::general:
        weight = -(value/25.0);
        GaussianBlur(src, dst, Size(0,0), 10, 0);
        addWeighted(src, 1 - weight, dst, weight, 0, dst);
        break;

    case Sharpen::laplacian:
        weight = -(value/50.0);
        cv::Laplacian(src, dst, CV_32F, 3);
        addWeighted(copy, 1 - weight, dst, weight, 0, dst);
        dst.convertTo(dst, CV_8UC2);
        break;
    }
    imshow("Preview", dst);
}

void Sharpen::rejected()
{
    if(General->isChecked())
    {
        General->setAutoExclusive(false);
        General->setChecked(false);
        General->setAutoExclusive(true);
        generalSlider->setValue(0);
        generalSlider->setDisabled(true);
        }
    else
    {
        Laplacian->setAutoExclusive(false);
        Laplacian->setChecked(false);
        Laplacian->setAutoExclusive(true);
        laplacianSlider->setValue(0);
        laplacianSlider->setDisabled(true);
    }
}

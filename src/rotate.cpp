#include "rotate.h"

Rotate::Rotate(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
    dst = src.clone();
}

void Rotate::buttonDown()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button == vertical)
    {
        flip(dst, dst, 0);
    }
    else if(button == horizontal)
    {
        flip(dst, dst, 1);
    }
    else if(button == counterclockwise)
    {
        transpose(dst, dst);
        flip(dst, dst, 0);
    }
    else
    {
        transpose(dst, dst);
        flip(dst, dst, 1);
    }
    imshow("Preview", dst);
}

void Rotate::rejected()
{
    dst = src.clone();
}

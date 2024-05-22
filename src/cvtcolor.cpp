#include "cvtcolor.h"

CvtColor::CvtColor(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
    dst = src.clone();
}

void CvtColor::TypeChanged()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == gray) type = GRAY;
    else if(button == hsv) type = HSV;
    else if(button == hsl) type = HSL;
    else type = YCRCB;

    color();
}

void CvtColor::color()
{
    dst = src.clone();
    switch (type) {
    case CvtColor::GRAY:
        if(src.channels() != 3)
            cvtColor(dst, dst, COLOR_GRAY2BGR);
        cvtColor(dst, dst, COLOR_BGR2GRAY);
        break;

    case CvtColor::HSV:
        if(src.channels() != 3)
            cvtColor(dst, dst, COLOR_GRAY2BGR);
        cvtColor(dst, dst, COLOR_BGR2HSV);
        break;

    case CvtColor::HSL:
        if(src.channels() != 3)
            cvtColor(dst, dst, COLOR_GRAY2BGR);
        cvtColor(dst, dst, COLOR_BGR2HLS);
        break;

    case CvtColor::YCRCB:
        if(src.channels() != 3)
            cvtColor(dst, dst, COLOR_GRAY2BGR);
        cvtColor(dst, dst, COLOR_BGR2YCrCb);
        break;

    default:
        return;
    }
    imshow("Preview", dst);
}

void CvtColor::rejected()
{
    switch (type) {
    case CvtColor::GRAY:
        gray->setAutoExclusive(false);
        gray->setChecked(false);
        gray->setAutoExclusive(true);
        break;

    case CvtColor::HSV:
        hsv->setAutoExclusive(false);
        hsv->setChecked(false);
        hsv->setAutoExclusive(true);
        break;

    case CvtColor::HSL:
        hsl->setAutoExclusive(false);
        hsl->setChecked(false);
        hsl->setAutoExclusive(true);
        break;

    case CvtColor::YCRCB:
        ycrcb->setAutoExclusive(false);
        ycrcb->setChecked(false);
        ycrcb->setAutoExclusive(true);
        break;

    default:
        return;
    }
}

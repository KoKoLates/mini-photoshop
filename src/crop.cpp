#include "crop.h"

Crop::Crop(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
    dst = src.clone();
}

void Crop::TypeChanged()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == self)
    {
        imshow("Preview", dst);
        setMouseCallback("Preview", Crop::onMouseSelf, this);
    }
    else if(button == rectangle)
    {
        imshow("Preview", dst);
        setMouseCallback("Preview", Crop::onMouseRect, this);
    }
}

void Crop::onMouseSelf(int event, int x, int y, int, void *param)
{
    Crop *self = (Crop*)param;
    Mat tempImg = self->dst.clone();
    if(event == EVENT_LBUTTONDOWN)
    {
        self->point.append(Point(x,y));
    }
    if(event == EVENT_RBUTTONDOWN)
    {

        Point2f s[4];
        for(int index = self->point.size() - 1, num = 0; index >= self->point.size() - 4 && num <4; index--, num++)
            s[num] = self->point[index];

        int height = sqrt(pow((s[0].x - s[1].x), 2) + pow((s[0].y - s[1].y), 2));
        int width = sqrt(pow((s[1].x - s[2].x), 2) + pow((s[1].y - s[2].y), 2));
        float ratio = height*1.0/width*1.0;

        Point2f d[4] = {{0,0},{0,400*ratio},{400, 400*ratio},{400,0}};
        Mat matrix;
        matrix = getPerspectiveTransform(s, d);
        cv::warpPerspective(tempImg , self->dst, matrix, Size(400,400*ratio));
        self->point.clear();
        imshow("Preview", self->dst);
    }
    else
    {
        if(self->point.size() <= 4 && self->point.size() != 0)
        {
            circle(tempImg, self->point[0], 5, Scalar(255,0,0), FILLED);
            for(int index = 0; index < self->point.size() - 1; index ++)
                line(tempImg, self->point[index], self->point[index + 1], Scalar(255,0,0), 5);
        }
        else if(self->point.size() > 4 && self->point.size() != 0)
        {
            for(int index = self->point.size() - 1; index >= self->point.size() - 4; index--)
                line(tempImg, self->point[index], self->point[index - 1], Scalar(255,0,0), 5);
        }
        imshow("Preview", tempImg);
    }
}

void Crop::onMouseRect(int event, int x, int y, int flags, void *param)
{
    Crop *self = (Crop*)param;
    Mat tempImg = self->dst.clone();

    if(event == EVENT_LBUTTONDOWN)
    {
        self->s = Point2f(x,y);
    }
    else if(event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    {
        cv::rectangle(tempImg, self->s, Point(x,y), Scalar(255,0,0), 5);
        imshow("Preview", tempImg);
    }
    else if(event == EVENT_LBUTTONUP)
    {
        self->d = Point2f(x,y);
    }
    else if(event == EVENT_RBUTTONDOWN)
    {
        int width = abs(self->s.x - self->d.x);
        int height = abs(self->s.y - self->d.y);
        Rect roi(self->s, Size(width,height));
        self->dst = tempImg(roi);
        imshow("Preview", self->dst);
    }
}

void Crop::rejected()
{
    dst = src.clone();
    if(rectangle->isChecked())
    {
        rectangle->setAutoExclusive(false);
        rectangle->setChecked(false);
        rectangle->setAutoExclusive(true);
    }
    else if(self->isChecked())
    {
        self->setAutoExclusive(false);
        self->setChecked(false);
        self->setAutoExclusive(true);
    }
}

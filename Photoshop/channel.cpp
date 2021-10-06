#include "channel.h"

Channel::Channel(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
    dst = src.clone();
    rows = src.rows;
    cols = src.cols;
    beta = 0;
}

void Channel::valueChanged(int value)
{
    QSlider *slider = qobject_cast<QSlider*>(sender());
    if(slider == blue)
    {
        if(src.channels() != 3) return;
        alpha_b = (value + 100)/100.00;
        dst = Mat::zeros(src.size(), src.type());
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
            }
        }
    }
    else if(slider == green)
    {
        if(src.channels() != 3) return;
        alpha_g = (value + 100)/100.00;
        dst = Mat::zeros(src.size(), src.type());
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
            }
        }
    }
    else if(slider == red)
    {
        if(src.channels() != 3) return;
        alpha_r = (value + 100)/100.00;
        dst = Mat::zeros(src.size(), src.type());
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
            }
        }
    }
    else if(slider == contrast)
    {
        alpha = (value + 100)/100.00;
        dst = Mat::zeros(src.size(), src.type());
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                if(src.channels() != 3)
                {
                    int p = src.at<uchar>(row, col);
                    dst.at<uchar>(row, col) = saturate_cast<uchar>(alpha*p + beta);
                }
                else
                {
                    int b = src.at<Vec3b>(row, col)[0];
                    int g = src.at<Vec3b>(row, col)[1];
                    int r = src.at<Vec3b>(row, col)[2];

                    dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
                    dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
                    dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
                }
            }
        }
    }
    else
    {
        beta = value;
        dst = Mat::zeros(src.size(), src.type());
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                if(src.channels() != 3)
                {
                    int p = src.at<uchar>(row, col);
                    dst.at<uchar>(row, col) = saturate_cast<uchar>(alpha*p + beta);
                }
                else
                {
                    int b = src.at<Vec3b>(row, col)[0];
                    int g = src.at<Vec3b>(row, col)[1];
                    int r = src.at<Vec3b>(row, col)[2];

                    dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
                    dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
                    dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
                }
            }
        }
    }
    imshow("Preview", dst);
}

void Channel::rejected()
{
    beta = 0;
    red->setValue(1.00);
    blue->setValue(1.00);
    green->setValue(1.00);
    contrast->setValue(1.00);
    brightness->setValue(1.00);
}


#include "color.h"

Color::Color(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
    dst = src.clone();
    rows = src.rows;
    cols = src.cols;
}

void Color::TypeChanged()
{
    if(src.channels() != 3) return;
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == red) type = RED;
    else if(button == green) type = GREEN;
    else if(button == blue) type = BLUE;
    else if(button == casting) type = CASTING;
    else if(button == comic) type = COMIC;
    else if(button == frozen) type = FROZEN;
    else if(button == reverse) type = REVERSE;
    else type = VINYAGE;

    filter();
}

void Color::filter()
{
    dst = Mat::zeros(src.size(), src.type());
    switch (type) {
    case Color::RED: {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                dst.at<Vec3b>(row, col)[0] = 0;
                dst.at<Vec3b>(row, col)[1] = 0;
                dst.at<Vec3b>(row, col)[2] = src.at<Vec3b>(row, col)[2];
            }
        }
        break;
    }
    case Color::BLUE: {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                dst.at<Vec3b>(row, col)[0] = src.at<Vec3b>(row, col)[0];
                dst.at<Vec3b>(row, col)[1] = 0;
                dst.at<Vec3b>(row, col)[2] = 0;
            }
        }
        break;
    }
    case Color::GREEN: {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                dst.at<Vec3b>(row, col)[0] = 0;
                dst.at<Vec3b>(row, col)[1] = src.at<Vec3b>(row, col)[1];
                dst.at<Vec3b>(row, col)[2] = 0;
            }
        }
        break;
    }
    case Color::CASTING: {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(b*128/(g + r + 1));
                dst.at<Vec3b>(row,col)[1] = saturate_cast<uchar>(g*128/(r + b + 1));
                dst.at<Vec3b>(row,col)[2] = saturate_cast<uchar>(r*128/(b + g + 1));
            }
        }
        break;
    }
    case Color::COMIC: {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];

                double B = abs(b - g + b + r) * g / 256;
                double G = abs(b - g + b + r) * r / 256;
                double R = abs(g - b + g + r) * r / 256;

                dst.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(B);
                dst.at<Vec3b>(row,col)[1] = saturate_cast<uchar>(G);
                dst.at<Vec3b>(row,col)[2] = saturate_cast<uchar>(R);
            }
        }
        break;
    }
    case Color::FROZEN: {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(abs(b - r - g)*3/2);
                dst.at<Vec3b>(row,col)[1] = saturate_cast<uchar>(abs(g - r - b)*3/2);
                dst.at<Vec3b>(row,col)[2] = saturate_cast<uchar>(abs(r - g - b)*3/2);
            }
        }
        break;
    }
    case Color::REVERSE: {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                for(int chennals = 0; chennals <3; chennals++)
                    dst.at<Vec3b>(row,col)[chennals] = 255 - src.at<Vec3b>(row,col)[chennals];
            }
        }
        break;
    }
    case Color::VINYAGE:{
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];
                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(0.272*b + 0.534*g + 0.131*r);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(0.168*b + 0.686*g + 0.349*r);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(0.189*b + 0.769*g + 0.393*r);
            }
        }
        break;
    }
    default:
        break;
    }
    imshow("Preview", dst);
}

void Color::rejected()
{
    switch (type) {
    case Color::RED:
        red->setAutoExclusive(false);
        red->setChecked(false);
        red->setAutoExclusive(true);
        break;

    case Color::BLUE:
        blue->setAutoExclusive(false);
        blue->setChecked(false);
        blue->setAutoExclusive(true);
        break;

    case Color::GREEN:
        green->setAutoExclusive(false);
        green->setChecked(false);
        green->setAutoExclusive(true);
        break;

    case Color::CASTING:
        casting->setAutoExclusive(false);
        casting->setChecked(false);
        casting->setAutoExclusive(true);
        break;

    case Color::COMIC:
        comic->setAutoExclusive(false);
        comic->setChecked(false);
        comic->setAutoExclusive(true);
        break;

    case Color::FROZEN:
        frozen->setAutoExclusive(false);
        frozen->setChecked(false);
        frozen->setAutoExclusive(true);
        break;

    case Color::REVERSE:
        reverse->setAutoExclusive(false);
        reverse->setChecked(false);
        reverse->setAutoExclusive(true);
        break;

    case Color::VINYAGE:
        vintage->setAutoExclusive(false);
        vintage->setChecked(false);
        vintage->setAutoExclusive(true);
        break;

    default:
        return;
    }
}

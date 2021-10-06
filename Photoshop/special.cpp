#include "special.h"

Special::Special(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
    dst = src.clone();
    rows = src.rows;
    cols = src.cols;
}

void Special::TypeChanged()
{
    if(src.channels() != 3) return;
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == dark) type = DARK;
    else if(button == light) type = LIGHT;
    else if(button == diagonal) type = DIAGONAL;
    else if(button == enrgaving) type = ENGRAVING;
    else if(button == noise) type = NOISE;
    else if(button == side) type = SIDE;
    else if(button == lightening) type = LIGHTENING;
    else type = VIGNETTING;

    filter();
}

void Special::filter()
{
    dst = Mat::zeros(src.size(), src.type());
    switch (type) {
    case Special::DARK: {
        Mat leak = imread("./images/dark.jpg");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(src,0.6,leak,0.4,0,dst);
        break;
    }
    case Special::LIGHT: {
        Mat leak = imread("./images/light.jpg");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(src,0.6,leak,0.4,0,dst);
        break;
    }
    case Special::DIAGONAL: {
        Mat leak = imread("./images/diagonal.png");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(src,0.6,leak,0.4,0,dst);
        break;
    }
    case Special::ENGRAVING: {
        Mat leak = imread("./images/engraving.png");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(src,0.6,leak,0.4,0,dst);
        break;
    }
    case Special::NOISE: {
        RNG rng;
        Mat noise(src.size(),src.type());
        randn(noise,rng.uniform(10,50),rng.uniform(1,80));
        dst = src + noise;
        break;
    }
    case Special::SIDE: {
        Mat leak = imread("./images/side.png");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(src,0.6,leak,0.4,0,dst);
        break;
    }
    case Special::LIGHTENING: {
        int centerX = cols >> 1;
        int centerY = rows >> 1;
        int s2 = pow(centerX,2) + pow(centerY,2);
        double ratio = cols > rows ? static_cast<double>(rows)/cols : static_cast<double>(cols)/rows;
        double Size = 0.5;
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                double dx = static_cast<double>(abs(centerX - static_cast<int>(col)));
                double dy = static_cast<double>(abs(centerY - static_cast<int>(row)));

                if(centerX > centerY) dx = ratio*dx;
                else dy = ratio*dx;

                double s1 = pow(dx,2) + pow(dy,2);
                double v = 255*s1/(s2*Size);

                int b = src.at<Vec3b>(row, col)[0];
                int g = src.at<Vec3b>(row, col)[1];
                int r = src.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b + v);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g + v);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r + v);
            }
        }
        break;
    }
    case Special::VIGNETTING: {
        Mat maskImg(src.size(), CV_64F);
        Point firstP = Point(maskImg.size().width/2, maskImg.size().height/2);
        double radius = 1.0, power = 0.8;
        double maxImgRadius = radius *getDistanceFromCorner(maskImg.size(), firstP);
        maskImg.setTo(Scalar(1));
        for(int i = 0; i < maskImg.rows; i++)
        {
            for(int j = 0; j < maskImg.cols; j++)
            {
                double temp = sqrt(pow((double)(firstP.x - Point(j, i).x), 2) + pow((double)(firstP.y - Point(j, i).y), 2))/maxImgRadius;
                temp *= power;
                double tempS = pow(cos(temp),4);
                maskImg.at<double>(i, j) = tempS;
            }
        }

        Mat gradient, lab(src.size(), CV_8UC3);
        normalize(maskImg, gradient, 0, 255, 32);
        cvtColor(src,lab,COLOR_BGR2Lab);

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                Vec3b value = lab.at<Vec3b>(row,col);
                value.val[0] *= maskImg.at<double>(row,col);
                lab.at<Vec3b>(row,col) = value;
            }
        }
        cvtColor(lab,dst,COLOR_Lab2BGR);
        break;
    }
    default:
        break;
    }
    imshow("Preview", dst);
}

void Special::rejected()
{
    switch (type) {
    case Special::DARK:
        dark->setAutoExclusive(false);
        dark->setChecked(false);
        dark->setAutoExclusive(true);
        break;

    case Special::LIGHT:
        light->setAutoExclusive(false);
        light->setChecked(false);
        light->setAutoExclusive(true);
        break;

    case Special::DIAGONAL:
        diagonal->setAutoExclusive(false);
        diagonal->setChecked(false);
        diagonal->setAutoExclusive(true);
        break;

    case Special::ENGRAVING:
        enrgaving->setAutoExclusive(false);
        enrgaving->setChecked(false);
        enrgaving->setAutoExclusive(true);
        break;

    case Special::NOISE:
        noise->setAutoExclusive(false);
        noise->setChecked(false);
        noise->setAutoExclusive(true);
        break;

    case Special::SIDE:
        side->setAutoExclusive(false);
        side->setChecked(false);
        side->setAutoExclusive(true);
        break;

    case Special::LIGHTENING:
        lightening->setAutoExclusive(false);
        lightening->setChecked(false);
        lightening->setAutoExclusive(true);
        break;

    case Special::VIGNETTING:
        vignetting->setAutoExclusive(false);
        vignetting->setChecked(false);
        vignetting->setAutoExclusive(true);
        break;

    default:
        return;
    }
}

double Special::getDistanceFromCorner(const Size &imgSize, const Point &center)
{
    vector<Point>corner(4);
    corner[0] = Point(0,0);
    corner[1] = Point(imgSize.width,0);
    corner[2] = Point(0,imgSize.height);
    corner[3] = Point(imgSize.width,imgSize.height);
    double maxDistance = 0.0;
    for(int i =0; i < 4; i++)
    {
        double dis = sqrt(pow((double)(corner[i].x - center.x), 2) + pow((double)(corner[i].y - center.y), 2));
        if(maxDistance < dis) maxDistance = dis;
    }
    return maxDistance;
}

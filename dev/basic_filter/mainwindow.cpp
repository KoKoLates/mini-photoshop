#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->open,SIGNAL(triggered()),this,SLOT(fileOpen()));
    connect(ui->color,SIGNAL(triggered()),this,SLOT(switchPages()));
    connect(ui->special,SIGNAL(triggered()),this,SLOT(switchPages()));

    connect(ui->vintage,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->red,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->green,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->blue,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->comic,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->casting,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->frozen,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->reverse,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->vignetting,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->lightening,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->noise,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->leak1,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->leak2,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->leak3,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->leak4,SIGNAL(clicked()),this,SLOT(TypeChanged()));
    connect(ui->leak5,SIGNAL(clicked()),this,SLOT(TypeChanged()));

    connect(ui->colorCheck,SIGNAL(accepted()),this,SLOT(accept()));
    connect(ui->filterCheck,SIGNAL(accepted()),this,SLOT(accept()));
    connect(ui->colorCheck,SIGNAL(rejected()),this,SLOT(reject()));
    connect(ui->filterCheck,SIGNAL(rejected()),this,SLOT(reject()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open Image"),"",tr("Image(*.png *.jpg *.jpeg)"));
    if(!filePath.isEmpty())
    {
        image = imread(filePath.toStdString().c_str());
        imshow("Image",image);
        rows = image.rows;
        cols = image.cols;
    }
}

void MainWindow::switchPages()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->color)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(action == ui->special)
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::TypeChanged()
{
    dst = Mat::zeros(image.size(), image.type());
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == ui->vintage)
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = image.at<Vec3b>(row, col)[0];
                int g = image.at<Vec3b>(row, col)[1];
                int r = image.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(0.272*b + 0.534*g + 0.131*r);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(0.168*b + 0.686*g + 0.349*r);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(0.189*b + 0.769*g + 0.393*r);
            }
        }
    }
    else if(button == ui->red)
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                dst.at<Vec3b>(row, col)[0] = 0;
                dst.at<Vec3b>(row, col)[1] = 0;
                dst.at<Vec3b>(row, col)[2] = image.at<Vec3b>(row, col)[2];
            }
        }
    }
    else if(button == ui->green)
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                dst.at<Vec3b>(row, col)[0] = 0;
                dst.at<Vec3b>(row, col)[1] = image.at<Vec3b>(row, col)[1];
                dst.at<Vec3b>(row, col)[2] = 0;
            }
        }
    }
    else if(button == ui->blue)
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                dst.at<Vec3b>(row, col)[0] = image.at<Vec3b>(row, col)[0];
                dst.at<Vec3b>(row, col)[1] = 0;
                dst.at<Vec3b>(row, col)[2] = 0;
            }
        }
    }
    else if(button == ui->comic)
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = image.at<Vec3b>(row, col)[0];
                int g = image.at<Vec3b>(row, col)[1];
                int r = image.at<Vec3b>(row, col)[2];

                double B = abs(b - g + b + r) * g / 256;
                double G = abs(b - g + b + r) * r / 256;
                double R = abs(g - b + g + r) * r / 256;

                dst.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(B);
                dst.at<Vec3b>(row,col)[1] = saturate_cast<uchar>(G);
                dst.at<Vec3b>(row,col)[2] = saturate_cast<uchar>(R);
            }
        }
    }
    else if(button == ui->casting)
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = image.at<Vec3b>(row, col)[0];
                int g = image.at<Vec3b>(row, col)[1];
                int r = image.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(b*128/(g + r + 1));
                dst.at<Vec3b>(row,col)[1] = saturate_cast<uchar>(g*128/(r + b + 1));
                dst.at<Vec3b>(row,col)[2] = saturate_cast<uchar>(r*128/(b + g + 1));
            }
        }
    }
    else if(button == ui->reverse)
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                for(int chennals = 0; chennals <3; chennals++) dst.at<Vec3b>(row,col)[chennals] = 255 - image.at<Vec3b>(row,col)[chennals];
            }
        }
    }
    else if(button == ui->frozen)
    {
        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                int b = image.at<Vec3b>(row, col)[0];
                int g = image.at<Vec3b>(row, col)[1];
                int r = image.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(abs(b - r - g)*3/2);
                dst.at<Vec3b>(row,col)[1] = saturate_cast<uchar>(abs(g - r - b)*3/2);
                dst.at<Vec3b>(row,col)[2] = saturate_cast<uchar>(abs(r - g - b)*3/2);
            }
        }
    }
    else if(button == ui->vignetting)
    {
        Mat maskImg(image.size(), CV_64F);
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

        Mat gradient, lab(image.size(), CV_8UC3);
        normalize(maskImg, gradient, 0, 255, 32);
        cvtColor(image,lab,COLOR_BGR2Lab);

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
    }
    else if(button == ui->lightening)
    {
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

                int b = image.at<Vec3b>(row, col)[0];
                int g = image.at<Vec3b>(row, col)[1];
                int r = image.at<Vec3b>(row, col)[2];

                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b + v);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g + v);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r + v);
            }
        }
    }
    else if(button == ui->noise)
    {
        RNG rng;
        Mat noise(image.size(),image.type());
        randn(noise,rng.uniform(10,50),rng.uniform(1,80));
        dst = image + noise;
    }
    else if(button == ui->leak1)
    {
        Mat leak = imread("C:/Users/acer/Desktop/images/leak1.png");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(image,0.6,leak,0.4,0,dst);
    }
    else if(button == ui->leak2)
    {
        Mat leak = imread("C:/Users/acer/Desktop/images/leak2.png");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(image,0.6,leak,0.4,0,dst);
    }
    else if(button == ui->leak3)
    {
        Mat leak = imread("C:/Users/acer/Desktop/images/leak3.png");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(image,0.6,leak,0.4,0,dst);
    }
    else if(button == ui->leak4)
    {
        Mat leak = imread("C:/Users/acer/Desktop/images/leak4.jpg");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(image,0.6,leak,0.4,0,dst);
    }
    else if(button == ui->leak5)
    {
        Mat leak = imread("C:/Users/acer/Desktop/images/leak5.jpg");
        cv::resize(leak,leak,Size(cols,rows));
        addWeighted(image,0.6,leak,0.4,0,dst);
    }
    imshow("Preview", dst);
}

double MainWindow::getDistanceFromCorner(const Size &imgSize, const Point &center)
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

void MainWindow::reject()
{
    QRadioButton *button;
    if(ui->vintage->isChecked()) button = ui->vintage;
    else if(ui->red->isChecked()) button = ui->red;
    else if(ui->green->isChecked()) button = ui->green;
    else if(ui->blue->isChecked()) button = ui->blue;
    else if(ui->comic->isChecked()) button = ui->comic;
    else if(ui->casting->isChecked()) button = ui->casting;
    else if(ui->frozen->isChecked()) button = ui->frozen;
    else if(ui->reverse->isChecked()) button = ui->reverse;
    else if(ui->vignetting->isChecked()) button = ui->vignetting;
    else if(ui->lightening->isChecked()) button = ui->lightening;
    else if(ui->noise->isChecked()) button = ui->noise;
    else if(ui->leak1->isChecked()) button = ui->leak1;
    else if(ui->leak2->isChecked()) button = ui->leak2;
    else if(ui->leak3->isChecked()) button = ui->leak3;
    else if(ui->leak4->isChecked()) button = ui->leak4;
    else if(ui->leak5->isChecked()) button = ui->leak5;

    button->setAutoExclusive(false);
    button->setChecked(false);
    button->setAutoExclusive(true);

    destroyWindow("Preview");
}

void MainWindow::accept()
{
    image = dst.clone();
    imshow("Image",image);
    emit ui->colorCheck->rejected();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connection();
    SliderInitialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connection()
{
    // connect all the signals (slider) to correspond slots
    connect(ui->Open, SIGNAL(triggered()), this, SLOT(fileOpen()));
    connect(ui->blue, SIGNAL(valueChanged(int)), this, SLOT(blueSlider(int)));
    connect(ui->green, SIGNAL(valueChanged(int)), this, SLOT(greenSlider(int)));
    connect(ui->red, SIGNAL(valueChanged(int)), this, SLOT(redSlider(int)));
    connect(ui->contrast, SIGNAL(valueChanged(int)), this, SLOT(contrastSlider(int)));
    connect(ui->brigthness, SIGNAL(valueChanged(int)), this, SLOT(brigthnessSlider(int)));
}

void MainWindow::SliderInitialize()
{
    // initialize the value ranges of each slider
    ui->blue->setMaximum(100);
    ui->blue->setMinimum(-70);

    ui->green->setMaximum(100);
    ui->green->setMinimum(-70);

    ui->red->setMaximum(100);
    ui->red->setMinimum(-70);

    ui->contrast->setMaximum(100);
    ui->contrast->setMinimum(-70);

    ui->brigthness->setMaximum(127);
    ui->brigthness->setMinimum(-127);
}

void MainWindow::fileOpen()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("OpenImage"),"", tr("Image(*.png *.jpg *.jpeg)"));    
    image = imread(filePath.toStdString());
    if(!image.empty()){
        qDebug() << "Success";
    }else qDebug() << "Fail";

    rows = image.rows;
    cols = image.cols;

    imshow("Image", image);
}


void MainWindow::blueSlider(int value){
    alpha_b = (value + 100)/100.00;
    Mat dst = Mat::zeros(image.size(), image.type());
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            int b = image.at<Vec3b>(row, col)[0];
            int g = image.at<Vec3b>(row, col)[1];
            int r = image.at<Vec3b>(row, col)[2];

            dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
            dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
        }
    }
    imshow("Image", dst);
}


void MainWindow::greenSlider(int value)
{
    alpha_g = (value + 100)/100.00;
    Mat dst = Mat::zeros(image.size(), image.type());
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            int b = image.at<Vec3b>(row, col)[0];
            int g = image.at<Vec3b>(row, col)[1];
            int r = image.at<Vec3b>(row, col)[2];

            dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
            dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
        }
    }
    imshow("Image", dst);
}

void MainWindow::redSlider(int value)
{
    alpha_r = (value + 100)/100.00;
    Mat dst = Mat::zeros(image.size(), image.type());
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            int b = image.at<Vec3b>(row, col)[0];
            int g = image.at<Vec3b>(row, col)[1];
            int r = image.at<Vec3b>(row, col)[2];

            dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
            dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
        }
    }
    imshow("Image", dst);
}


void MainWindow::contrastSlider(int value)
{
    alpha = (value + 100)/100.00;
    Mat dst = Mat::zeros(image.size(), image.type());
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            int b = image.at<Vec3b>(row, col)[0];
            int g = image.at<Vec3b>(row, col)[1];
            int r = image.at<Vec3b>(row, col)[2];

            dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
            dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
        }
    }
    imshow("Image", dst);
}

void MainWindow::brigthnessSlider(int value)
{
    beta = value;
    Mat dst = Mat::zeros(image.size(), image.type());
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            int b = image.at<Vec3b>(row, col)[0];
            int g = image.at<Vec3b>(row, col)[1];
            int r = image.at<Vec3b>(row, col)[2];

            dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*alpha_b*b + beta);
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*alpha_g*g + beta);
            dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*alpha_r*r + beta);
        }
    }
    imshow("Image", dst);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Open, SIGNAL(triggered()), this, SLOT(fileOpen()));
    connect(ui->saturation, SIGNAL(valueChanged(int)), this, SLOT(saturationSlider(int)));
    
    ui->saturation->setMaximum(50);
    ui->saturation->setMinimum(-50);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::saturationSlider(int value){
    float Increment = value / 100.0;
    Mat dst = Mat::zeros(image.size(), image.type());
    for(int row = 0; row <rows; row++){
        for(int col = 0; col <cols; col++){

            int b = image.at<Vec3b>(row, col)[0];
            int g = image.at<Vec3b>(row, col)[1];
            int r = image.at<Vec3b>(row, col)[2];

            float maxn = max(b,max(g,r));
            float minn = min(b,min(g,r));
            float delta, value, L, S, Alpha;

            delta = (maxn - minn)/255;
            value = (maxn + minn)/255;
            L = value/2;

            if(L < 0.5) S = delta/value;
            else S = delta/(2 - value);

            if(Increment >= 0){
                if((Increment + S) >= 1) Alpha = S;
                else Alpha =  (1/(1 - Increment)) - 1;

                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>((b - 255*L)*Alpha + b);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>((g - 255*L)*Alpha + g);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>((r - 255*L)*Alpha + r);
            }
            else{
                Alpha = Increment;
                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>((b - 255*L)*(Alpha + 1) + 255*L);
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>((g - 255*L)*(Alpha + 1) + 255*L);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>((r - 255*L)*(Alpha + 1) + 255*L);
            }
        }
    }
    imshow("Image", dst);
}

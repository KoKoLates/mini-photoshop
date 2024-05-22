#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->checkBox, SIGNAL(accepted()), this, SLOT(check()));
    connect(ui->checkBox, SIGNAL(rejected()), this, SLOT(rejected()));

    //file input
    QString filePath = QFileDialog::getOpenFileName(this, tr("ImageOpen"), "", tr("Image(*.png *.jpg *.jpeg)"));
    image = imread(filePath.toStdString().c_str());
    imshow("Image", image);
    waitKey(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check()
{
    Mat dst = image.clone();
    if(ui->Gray->isChecked())
    {
        cvtColor(dst, dst, COLOR_BGR2GRAY);
    }
    else if(ui->HSV->isChecked())
    {
        cvtColor(dst, dst, COLOR_BGR2HSV);
    }
    else if(ui->HSL->isChecked())
    {
        cvtColor(dst, dst, COLOR_BGR2HLS);
    }
    else if(ui->YCrCb->isChecked())
    {
        cvtColor(dst, dst, COLOR_BGR2YCrCb);
    }
    imshow("Image", dst);
}

void MainWindow::rejected()
{
    if(ui->Gray->isChecked())
    {
        ui->Gray->setAutoExclusive(false);
        ui->Gray->setChecked(false);
        ui->Gray->setAutoExclusive(true);
    }
    else if(ui->HSV->isChecked())
    {
        ui->HSV->setAutoExclusive(false);
        ui->HSV->setChecked(false);
        ui->HSV->setAutoExclusive(true);
    }
    else if(ui->HSL->isChecked())
    {
        ui->HSL->setAutoExclusive(false);
        ui->HSL->setChecked(false);
        ui->HSL->setAutoExclusive(true);
    }
    else if(ui->YCrCb->isChecked())
    {
        ui->YCrCb->setAutoExclusive(false);
        ui->YCrCb->setChecked(false);
        ui->YCrCb->setAutoExclusive(true);
    }
    imshow("Image", image);
}

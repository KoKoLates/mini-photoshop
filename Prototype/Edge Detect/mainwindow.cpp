#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Sobel, SIGNAL(clicked()), this, SLOT(TypeChanged()));
    connect(ui->Scharr, SIGNAL(clicked()), this, SLOT(TypeChanged()));
    connect(ui->Laplacian, SIGNAL(clicked()), this, SLOT(TypeChanged()));
    connect(ui->Canny, SIGNAL(clicked()), this, SLOT(TypeChanged()));
    connect(ui->detectCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->detectCheck, SIGNAL(rejected()), this, SLOT(reject()));
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image(*.png *.jpg *.jpeg)"));
    if(!filePath.isEmpty())
    {
        src = imread(filePath.toStdString().c_str());
        imshow("Image", src);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TypeChanged()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == ui->Sobel) type = sobel;
    else if(button == ui->Scharr) type = scharr;
    else if(button == ui->Laplacian) type = laplacian;
    else if(button == ui->Canny) type = canny;
    edgeDetect();
}

void MainWindow::edgeDetect()
{
    switch (type) {
    case MainWindow::sobel :
        cvtColor(src, dst, COLOR_BGR2GRAY);
        Sobel(dst, x, CV_16S, 1, 0);
        Sobel(dst, y, CV_16S, 0, 1);
        convertScaleAbs(x, x);
        convertScaleAbs(y, y);
        addWeighted(x, 0.5, y, 0.5, 0, dst);
        break;

    case MainWindow::scharr :
        cvtColor(src, dst, COLOR_BGR2GRAY);
        Scharr(dst, x, CV_16S, 1, 0);
        Scharr(dst, y, CV_16S, 0, 1);
        convertScaleAbs(x, x);
        convertScaleAbs(y, y);
        addWeighted(x, 0.5, y, 0.5, 0, dst);
        break;

    case MainWindow::laplacian :
        cvtColor(src, dst, COLOR_BGR2GRAY);
        Laplacian(dst, dst, -1, 5);
        break;

    case MainWindow::canny :
        cvtColor(src, dst, COLOR_BGR2GRAY);
        Canny(dst, dst, 50, 150);
        break;

    default:
        dst = src.clone();
    }

    imshow("Preview", dst);
}

void MainWindow::accept()
{
    src = dst.clone();
    imshow("Image", src);
    emit ui->detectCheck->rejected();
}

void MainWindow::reject()
{
    QRadioButton *button;
    if(ui->Sobel->isChecked()) button = ui->Sobel;
    else if(ui->Scharr->isChecked()) button = ui->Scharr;
    else if(ui->Laplacian->isChecked()) button = ui->Laplacian;
    else button = ui->Canny;

    button->setAutoExclusive(false);
    button->setChecked(false);
    button->setAutoExclusive(true);

    destroyWindow("Preview");
}

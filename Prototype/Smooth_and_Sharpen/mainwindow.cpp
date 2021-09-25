#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->smooth, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->sharpen, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->blurCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ui->blurCheck, SIGNAL(accepted()), this, SLOT(accept()));

    ui->blurKernel->setMinimum(1);
    ui->blurKernel->setMaximum(17);
    ui->blurKernel->setSingleStep(2);

    ui->generalSlider->setMaximum(25);
    ui->generalSlider->setMinimum(0);
    ui->generalSlider->setDisabled(true);
    ui->laplacianSlider->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileProcess()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->open)
    {
        QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image(*.png *.jpg *. jpeg)"));
        image = imread(filePath.toStdString().c_str());
        if(!image.empty())
        {
            newFilter();
            newSharpen();
            imshow("Image", image);
        }
    }
    else if(action == ui->save)
    {
        qDebug() << "image is saved";
    }
}

void MainWindow::switchPages()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->smooth) ui->stackedWidget->setCurrentIndex(1);
    else if(action == ui->sharpen) ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::accept()
{
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->blurCheck)
    {
        image = filter->blurDone().clone();
        emit ui->blurCheck->rejected();
    }
    imshow("Image", image);
    delete filter;
    newFilter();
}

void MainWindow::reject()
{
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->blurCheck)
    {
        QRadioButton *rButton;

        if(ui->Box->isChecked()) rButton = ui->Box;
        else if(ui->Gaussian->isChecked()) rButton = ui->Gaussian;
        else if(ui->Median->isChecked()) rButton = ui->Median;
        else rButton = ui->Bilateral;

        rButton->setAutoExclusive(false);
        rButton->setChecked(false);
        rButton->setAutoExclusive(true);

        ui->blurKernel->setValue(1);
    }
    destroyWindow("Preview");
}

void MainWindow::newFilter()
{
    filter = new Filter(this, image);

    filter->Box = ui->Box;
    filter->Gaussian = ui->Gaussian;
    filter->Median = ui->Median;
    filter->Bilateral = ui->Bilateral;

    connect(ui->Box, SIGNAL(clicked()), filter, SLOT(filterChanged()));
    connect(ui->Gaussian, SIGNAL(clicked()), filter, SLOT(filterChanged()));
    connect(ui->Median, SIGNAL(clicked()), filter, SLOT(filterChanged()));
    connect(ui->Bilateral, SIGNAL(clicked()), filter, SLOT(filterChanged()));
    connect(ui->blurKernel, SIGNAL(valueChanged(int)), filter, SLOT(kernelChanged(int)));
}

void MainWindow::newSharpen()
{
    sharpen = new Sharpen(this, image);

    sharpen->General = ui->General;
    sharpen->Laplacian = ui->Laplacian;
    sharpen->generalSlider = ui->generalSlider;
    sharpen->laplacianSlider = ui->laplacianSlider;

    connect(ui->General, SIGNAL(clicked()), sharpen, SLOT(TypeChanged()));
    connect(ui->Laplacian, SIGNAL(clicked()), sharpen, SLOT(TypeChanged()));
    connect(ui->generalSlider, SIGNAL(valueChanged(int)), sharpen, SLOT(valueChanged(int)));
    connect(ui->laplacianSlider, SIGNAL(valueChanged(int)), sharpen, SLOT(valueChanged(int)));
}







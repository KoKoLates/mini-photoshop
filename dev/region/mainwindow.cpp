#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drag_and_drop.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setAcceptDrops(true);

    ui->blurKernel->setMinimum(1);
    ui->blurKernel->setMaximum(17);
    ui->blurKernel->setSingleStep(2);

    ui->generalSlider->setMaximum(25);
    ui->generalSlider->setMinimum(0);
    ui->generalSlider->setDisabled(true);

    ui->laplacianSlider->setMaximum(25);
    ui->laplacianSlider->setMinimum(0);
    ui->laplacianSlider->setDisabled(true);

    connect(ui->open, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->smooth, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->sharpen, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->blurCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ui->sharpenCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ui->blurCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->sharpenCheck, SIGNAL(accepted()), this, SLOT(accept()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileProcess()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->open && image.empty())
    {
        QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image(*.png *.jpg *.jpeg)"));
        if(!filePath.isEmpty())
        {
            image = imread(filePath.toStdString().c_str());
            imshow("Image", image);
        }
    }
    else if(action == ui->save && !image.empty())
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "",tr("Image(*.png *.jpg)"));
        if(!filePath.isEmpty())
        {
            imwrite(filePath.toStdString().c_str(), image);
            image.release();
            destroyWindow("Image");
            ui->stackedWidget->setCurrentIndex(0);
        }
    }
}

void MainWindow::switchPages()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->smooth)
    {
        ui->stackedWidget->setCurrentIndex(1);
        newSmooth();
    }
    else if(action == ui->sharpen)
    {
        ui->stackedWidget->setCurrentIndex(2);
        newSharpen();
    }
}

void MainWindow::accept()
{
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->blurCheck)
    {
        image = smooth->smoothDone().clone();
        emit ui->blurCheck->rejected();
        delete smooth;
    }
    else if(button == ui->sharpenCheck)
    {
        image = sharpen->sharpenDone().clone();
        emit ui->sharpenCheck->rejected();
        delete sharpen;
    }
    imshow("Image", image);
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
    else if(button == ui->sharpenCheck)
    {
        if(ui->General->isChecked())
        {
            ui->General->setAutoExclusive(false);
            ui->General->setChecked(false);
            ui->General->setAutoExclusive(true);
            ui->generalSlider->setValue(0);
            ui->generalSlider->setDisabled(true);
        }
        else
        {
            ui->Laplacian->setAutoExclusive(false);
            ui->Laplacian->setChecked(false);
            ui->Laplacian->setAutoExclusive(true);
            ui->laplacianSlider->setValue(0);
            ui->laplacianSlider->setDisabled(true);
        }
    }
    destroyWindow("Preview");
}

void MainWindow::newSmooth()
{
    smooth = new Smooth(this,image);

    smooth->Box = ui->Box;
    smooth->Gaussian = ui->Gaussian;
    smooth->Median = ui->Median;
    smooth->Bilateral = ui->Bilateral;

    connect(ui->Box, SIGNAL(clicked()), smooth, SLOT(TypeChanged()));
    connect(ui->Gaussian, SIGNAL(clicked()), smooth, SLOT(TypeChanged()));
    connect(ui->Median, SIGNAL(clicked()), smooth, SLOT(TypeChanged()));
    connect(ui->Bilateral, SIGNAL(clicked()), smooth, SLOT(TypeChanged()));
    connect(ui->blurKernel, SIGNAL(valueChanged(int)), smooth, SLOT(kernelChanged(int)));
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

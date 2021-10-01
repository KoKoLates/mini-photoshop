#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drag_drop.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setAcceptDrops(true);

    connect(ui->Open, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->Save, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->Size, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Blur, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Channel, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Sharpen, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->ColorModel, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Color, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Special, SIGNAL(triggered()), this, SLOT(switchPages()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileProcess()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->Open && image.empty())
    {

        QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image(*.png *.jpg *.jpeg)"));
        if(!filePath.isEmpty())
        {
            image = imread(filePath.toStdString().c_str());
            imshow("Image", image);
        }
        emit ui->Size->triggered();
    }
    else if(action == ui->Save && !image.empty())
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
    if(action == ui->Size)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(action == ui->Blur)
    {
        ui->stackedWidget->setCurrentIndex(2);
        ui->kernel->setMinimum(1);
        ui->kernel->setMaximum(17);
        ui->kernel->setSingleStep(2);
        newBlur();
    }
    else if(action == ui->ColorModel)
    {
        ui->stackedWidget->setCurrentIndex(3);
        newColorSpace();
    }
    else if(action == ui->Channel)
    {
        ui->stackedWidget->setCurrentIndex(4);
        ui->blueSlider->setMaximum(100);
        ui->blueSlider->setMinimum(-70);
        ui->greenSlider->setMaximum(100);
        ui->greenSlider->setMinimum(-70);
        ui->redSlider->setMaximum(100);
        ui->redSlider->setMinimum(-70);
        ui->contrastSlider->setMaximum(100);
        ui->contrastSlider->setMinimum(-70);
        ui->brightnessSlider->setMaximum(127);
        ui->brightnessSlider->setMinimum(-127);
        newChannel();
    }
    else if(action == ui->Sharpen)
    {
        ui->stackedWidget->setCurrentIndex(5);
        ui->generalSlider->setMaximum(25);
        ui->generalSlider->setMinimum(0);
        ui->generalSlider->setDisabled(true);
        ui->laplacianSlider->setMaximum(25);
        ui->laplacianSlider->setMinimum(0);
        ui->laplacianSlider->setDisabled(true);
        newSharpen();
    }
    else if(action == ui->Color)
    {
        ui->stackedWidget->setCurrentIndex(6);
    }
    else
        ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::accept()
{
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->blurCheck)
    {
        image = blur->smoothDone().clone();
        emit ui->blurCheck->rejected();
        newBlur();
    }
    else if(button == ui->sharpenCheck)
    {
        image = sharpen->sharpenDone().clone();
        emit ui->sharpenCheck->rejected();
        newSharpen();
    }
    else if(button == ui->colorMCheck)
    {
        image = colorM->colorMDone().clone();
        emit ui->colorMCheck->rejected();
        //newColorSpace();
    }
    else if(button == ui->channelCheck)
    {
        image = channel->channelDone().clone();
        emit ui->channelCheck->rejected();
        newChannel();
    }
    imshow("Image", image);
}

void MainWindow::reject()
{
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->blurCheck)
    {
        emit cleanBlur();
        ui->kernel->setValue(1);
    }
    else if(button == ui->sharpenCheck)
        emit cleanSharpen();
    else if(button == ui->colorMCheck)
        emit cleanColorM();
    else if(button == ui->channelCheck)
        emit cleanChannel();
    destroyWindow("Preview");
}

void MainWindow::newBlur()
{
    blur = new Blur(this,image);

    blur->Box = ui->box;
    blur->Gaussian = ui->gaussian;
    blur->Median = ui->median;
    blur->Bilateral = ui->bilateral;

    connect(ui->box, SIGNAL(clicked()), blur, SLOT(TypeChanged()));
    connect(ui->gaussian, SIGNAL(clicked()), blur, SLOT(TypeChanged()));
    connect(ui->median, SIGNAL(clicked()), blur, SLOT(TypeChanged()));
    connect(ui->bilateral, SIGNAL(clicked()), blur, SLOT(TypeChanged()));
    connect(ui->kernel, SIGNAL(valueChanged(int)), blur, SLOT(kernelChanged(int)));
    connect(ui->blurCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->blurCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanBlur()), blur, SLOT(rejected()));
}

void MainWindow::newSharpen()
{
    sharpen = new Sharpen(this,image);

    sharpen->General = ui->general;
    sharpen->Laplacian = ui->laplacian;
    sharpen->generalSlider = ui->generalSlider;
    sharpen->laplacianSlider = ui->laplacianSlider;

    connect(ui->general, SIGNAL(clicked()), sharpen, SLOT(TypeChanged()));
    connect(ui->laplacian, SIGNAL(clicked()), sharpen, SLOT(TypeChanged()));
    connect(ui->generalSlider, SIGNAL(valueChanged(int)), sharpen, SLOT(valueChanged(int)));
    connect(ui->laplacianSlider, SIGNAL(valueChanged(int)), sharpen, SLOT(valueChanged(int)));
    connect(ui->sharpenCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->sharpenCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanSharpen()), sharpen, SLOT(rejected()));
}

void MainWindow::newColorSpace()
{
    colorM = new ColorSpace(this,image);

    colorM->gray = ui->gray;
    colorM->hsv = ui->hsv;
    colorM->hsl = ui->hsl;
    colorM->ycrcb = ui->ycrcb;

    connect(ui->gray, SIGNAL(clicked()), colorM, SLOT(TypeChanged()));
    connect(ui->hsv, SIGNAL(clicked()), colorM, SLOT(TypeChanged()));
    connect(ui->hsl, SIGNAL(clicked()), colorM, SLOT(TypeChanged()));
    connect(ui->ycrcb, SIGNAL(clicked()), colorM, SLOT(TypeChanged()));
    connect(ui->colorMCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->colorMCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanColorM()), colorM, SLOT(rejected()));
}

void MainWindow::newChannel()
{
    channel = new Channel(this,image);

    channel->red = ui->redSlider;
    channel->blue = ui->blueSlider;
    channel->green = ui->greenSlider;
    channel->contrast = ui->contrastSlider;
    channel->brightness = ui->brightnessSlider;

    connect(ui->redSlider, SIGNAL(valueChanged(int)), channel, SLOT(valueChanged(int)));
    connect(ui->blueSlider, SIGNAL(valueChanged(int)), channel, SLOT(valueChanged(int)));
    connect(ui->greenSlider, SIGNAL(valueChanged(int)), channel, SLOT(valueChanged(int)));
    connect(ui->contrastSlider, SIGNAL(valueChanged(int)), channel, SLOT(valueChanged(int)));
    connect(ui->brightnessSlider, SIGNAL(valueChanged(int)), channel, SLOT(valueChanged(int)));
    connect(ui->channelCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->channelCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanChannel()), channel, SLOT(rejected()));
}

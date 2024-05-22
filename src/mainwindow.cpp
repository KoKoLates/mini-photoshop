#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "event.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setAcceptDrops(true);

    connect(ui->open, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->Blur, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Channel, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Sharpen, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->CvtColor, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Color, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Special, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Crop, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Rotate, SIGNAL(triggered()), this, SLOT(switchPages()));
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
            emit ui->Crop->triggered();
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
    if(!image.empty())
    {
        QAction *action = qobject_cast<QAction*>(sender());
        if(action == ui->Blur)
        {
            ui->stackedWidget->setCurrentIndex(1);
            ui->kernel->setMinimum(1);
            ui->kernel->setMaximum(17);
            ui->kernel->setSingleStep(2);
            newBlur();
        }
        else if(action == ui->CvtColor)
        {
            ui->stackedWidget->setCurrentIndex(2);
            newCvtColor();
        }
        else if(action == ui->Channel)
        {
            ui->stackedWidget->setCurrentIndex(3);
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
            ui->stackedWidget->setCurrentIndex(4);
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
            ui->stackedWidget->setCurrentIndex(5);
            newColor();
        }
        else if(action == ui->Special)
        {
            ui->stackedWidget->setCurrentIndex(6);
            newSpecial();
        }
        else if(action == ui->Crop)
        {
            ui->stackedWidget->setCurrentIndex(7);
            ui->sizeSlider->setMaximum(12);
            ui->sizeSlider->setMinimum(-8);
            newCrop();
            newResize();
        }
        else if(action == ui->Rotate)
        {
            ui->stackedWidget->setCurrentIndex(8);
            newRotate();
        }
    }
    else return;
}

void MainWindow::accept()
{
    pastImg = image.clone();
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->blurCheck)
    {
        image = blur->blurFinish();
        emit ui->blurCheck->rejected();
        delete blur;
        newBlur();
    }
    else if(button == ui->sharpenCheck)
    {
        image = sharpen->sharpenFinish();
        emit ui->sharpenCheck->rejected();
        delete sharpen;
        newSharpen();
    }
    else if(button == ui->cvtCheck)
    {
        image = cvt->cvtFinish();
        emit ui->cvtCheck->rejected();
        delete cvt;
        newCvtColor();
    }
    else if(button == ui->channelCheck)
    {
        image = channel->channelFinish();
        emit ui->channelCheck->rejected();
        delete channel;
        newChannel();
    }
    else if(button == ui->colorCheck)
    {
        image = color->colorFinish();
        emit ui->colorCheck->rejected();
        delete color;
        newColor();
    }
    else if(button == ui->specialCheck)
    {
        image = special->specialFinish();
        emit ui->specialCheck->rejected();
        delete special;
        newSpecial();
    }
    else if(button == ui->sizeCheck)
    {
        image = size->sizeFinish();
        emit ui->sizeCheck->rejected();
        delete size;
        newResize();
    }
    else if(button == ui->rotateCheck)
    {
        image = rotate->rotateFinish();
        emit ui->rotateCheck->rejected();
        delete rotate;
        newRotate();
    }
    else if(button == ui->cropCheck)
    {
        image = crop->cropFinish();
        emit ui->cropCheck->rejected();
        delete crop;
        newCrop();
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
    {
        emit cleanSharpen();
    }
    else if(button == ui->cvtCheck)
    {
        emit cleanCvtColor();
    }
    else if(button == ui->channelCheck)
    {
        emit cleanChannel();
    }
    else if(button == ui->colorCheck)
    {
        emit cleanColor();
    }
    else if(button == ui->specialCheck)
    {
        emit cleanSpecial();
    }
    else if(button == ui->sizeCheck)
    {
        emit cleanResize();
    }
    else if (button == ui->rotateCheck)
    {
        emit cleanRotate();
    }
    else if(button == ui->cropCheck)
    {
        emit cleanCrop();
    }
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

void MainWindow::newCvtColor()
{
    cvt = new CvtColor(this,image);

    cvt->gray = ui->gray;
    cvt->hsv = ui->hsv;
    cvt->hsl = ui->hsl;
    cvt->ycrcb = ui->ycrcb;

    connect(ui->gray, SIGNAL(clicked()), cvt, SLOT(TypeChanged()));
    connect(ui->hsv, SIGNAL(clicked()), cvt, SLOT(TypeChanged()));
    connect(ui->hsl, SIGNAL(clicked()), cvt, SLOT(TypeChanged()));
    connect(ui->ycrcb, SIGNAL(clicked()), cvt, SLOT(TypeChanged()));
    connect(ui->cvtCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->cvtCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanCvtColor()), cvt, SLOT(rejected()));
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

void MainWindow::newColor()
{
    color = new Color(this,image);

    color->red = ui->redEffect;
    color->blue = ui->blueEffect;
    color->green = ui->greenEffect;
    color->casting = ui->casting;
    color->comic = ui->comic;
    color->frozen = ui->frozen;
    color->reverse = ui->reverse;
    color->vintage = ui->vintage;

    connect(ui->vintage, SIGNAL(clicked()), color, SLOT(TypeChanged()));
    connect(ui->redEffect, SIGNAL(clicked()), color, SLOT(TypeChanged()));
    connect(ui->greenEffect, SIGNAL(clicked()), color ,SLOT(TypeChanged()));
    connect(ui->blueEffect, SIGNAL(clicked()), color, SLOT(TypeChanged()));
    connect(ui->comic, SIGNAL(clicked()), color, SLOT(TypeChanged()));
    connect(ui->casting, SIGNAL(clicked()), color, SLOT(TypeChanged()));
    connect(ui->frozen, SIGNAL(clicked()), color, SLOT(TypeChanged()));
    connect(ui->reverse, SIGNAL(clicked()), color, SLOT(TypeChanged()));
    connect(ui->colorCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->colorCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanColor()), color, SLOT(rejected()));
}

void MainWindow::newSpecial()
{
    special = new Special(this,image);

    special->dark = ui->darkStripe;
    special->light = ui->lightStripe;
    special->diagonal = ui->diagonal;
    special->enrgaving = ui->engraving;
    special->noise = ui->noise;
    special->side = ui->side;
    special->lightening = ui->lightening;
    special->vignetting = ui->vignetting;

    connect(ui->darkStripe, SIGNAL(clicked()), special, SLOT(TypeChanged()));
    connect(ui->lightStripe, SIGNAL(clicked()), special, SLOT(TypeChanged()));
    connect(ui->diagonal, SIGNAL(clicked()), special ,SLOT(TypeChanged()));
    connect(ui->engraving, SIGNAL(clicked()), special, SLOT(TypeChanged()));
    connect(ui->noise, SIGNAL(clicked()), special, SLOT(TypeChanged()));
    connect(ui->side, SIGNAL(clicked()), special, SLOT(TypeChanged()));
    connect(ui->lightening, SIGNAL(clicked()), special, SLOT(TypeChanged()));
    connect(ui->vignetting, SIGNAL(clicked()), special, SLOT(TypeChanged()));
    connect(ui->specialCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->specialCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanSpecial()), special, SLOT(rejected()));
}

void MainWindow::newResize()
{
    size = new Resize(this, image);
    size->sizeSlider = ui->sizeSlider;
    connect(ui->sizeSlider, SIGNAL(valueChanged(int)), size, SLOT(valueChanged(int)));
    connect(ui->sizeCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->sizeCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanResize()), size, SLOT(rejected()));
}

void MainWindow::newRotate()
{
    rotate = new Rotate(this,image);

    rotate->vertical = ui->vertical;
    rotate->horizontal = ui->horizontal;
    rotate->counterclockwise = ui->cclockwise;
    rotate->clockwise = ui->clockwise;

    connect(ui->vertical, SIGNAL(clicked()), rotate, SLOT(buttonDown()));
    connect(ui->horizontal, SIGNAL(clicked()), rotate, SLOT(buttonDown()));
    connect(ui->cclockwise, SIGNAL(clicked()), rotate, SLOT(buttonDown()));
    connect(ui->clockwise, SIGNAL(clicked()), rotate, SLOT(buttonDown()));
    connect(ui->rotateCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->rotateCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanRotate()), rotate, SLOT(rejected()));
}

void MainWindow::newCrop()
{
    crop = new Crop(this,image);
    crop->self = ui->selfselect;
    crop->rectangle = ui->rectangle;

    connect(ui->selfselect, SIGNAL(clicked()), crop, SLOT(TypeChanged()));
    connect(ui->rectangle, SIGNAL(clicked()), crop, SLOT(TypeChanged()));
    connect(ui->cropCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->cropCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanCrop()), crop, SLOT(rejected()));
}

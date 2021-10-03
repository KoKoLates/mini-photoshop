#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->open, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->crop, SIGNAL(triggered()), this, SLOT(switchPages()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileProcess()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image(*.png *.jpg *.jpeg)"));
    if(!filePath.isEmpty())
    {
        image = imread(filePath.toStdString().c_str());
        imshow("Image", image);
    }
}

void MainWindow::switchPages()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->crop)
    {
        ui->stackedWidget->setCurrentIndex(1);
        newCrop();
    }
}

void MainWindow::accept()
{
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->cropCheck)
    {
        image = crop->cropDone().clone();
        emit ui->cropCheck->rejected();
        newCrop();
    }
    imshow("Image", image);
}

void MainWindow::reject()
{
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->cropCheck)
    {
        emit cleanCrop();
    }
    destroyWindow("Preview");
}

void MainWindow::newCrop()
{
    crop = new Crop(this,image);

    crop->self = ui->self;
    crop->rectangle = ui->rectangle;

    connect(ui->self, SIGNAL(clicked()), crop, SLOT(self1()));
    connect(ui->rectangle, SIGNAL(clicked()), crop, SLOT(rectangle1()));
    connect(ui->cropCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->cropCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanCrop()), crop, SLOT(rejected()));
}


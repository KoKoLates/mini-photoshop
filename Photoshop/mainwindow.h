#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "blur.h"
#include "sharpen.h"
#include "channel.h"
#include "cvtcolor.h"
#include "color.h"
#include "special.h"
#include "resize.h"
#include "rotate.h"
#include "crop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void newBlur();
    void newSharpen();
    void newChannel();
    void newCvtColor();
    void newColor();
    void newSpecial();
    void newResize();
    void newRotate();
    void newCrop();

private:
    Ui::MainWindow *ui;
    Mat image;
    Blur *blur;
    Sharpen *sharpen;
    Channel *channel;
    CvtColor *cvt;
    Color *color;
    Special *special;
    Resize *size;
    Rotate *rotate;
    Crop *crop;
    Mat pastImg;

signals:
    void cleanBlur();
    void cleanChannel();
    void cleanSharpen();
    void cleanCvtColor();
    void cleanColor();
    void cleanSpecial();
    void cleanResize();
    void cleanRotate();
    void cleanCrop();

private slots:
    void fileProcess();
    void switchPages();
    void accept();
    void reject();

protected:
    void dropEvent(QDropEvent*);
    void closeEvent(QCloseEvent*);
    void dragEnterEvent(QDragEnterEvent*);
};
#endif // MAINWINDOW_H

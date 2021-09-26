#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "smooth.h"
#include "sharpen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    cv::Mat image;
    void newSmooth();
    void newSharpen();

private:
    Ui::MainWindow *ui;
    Smooth *smooth;
    Sharpen *sharpen;

private slots:
    void switchPages();
    void fileProcess();
    void accept();
    void reject();

protected:
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);
};
#endif // MAINWINDOW_H

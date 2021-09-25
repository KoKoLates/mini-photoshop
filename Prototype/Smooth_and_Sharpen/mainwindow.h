#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "filter.h"
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
    void newFilter();
    void newSharpen();

private:
    Ui::MainWindow *ui;
    Filter *filter;
    Sharpen *sharpen;

private slots:
    void switchPages();
    void fileProcess();
    void accept();
    void reject();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connection();
    void SliderInitialize();
    cv::Mat image;

private:
    Ui::MainWindow *ui;
    
    int rows, cols;
    int beta = 0;
    float alpha = 1.00, alpha_b = 1.00, alpha_g = 1.00, alpha_r = 1.00;

public slots:
    void fileOpen();
    void blueSlider(int);
    void greenSlider(int);
    void redSlider(int);
    void contrastSlider(int);
    void brightnessSlider(int);
    
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    cv::Mat image, dst;
    double getDistanceFromCorner(const cv::Size &imgSize, const cv::Point &center);

private:
    Ui::MainWindow *ui;
    int rows, cols;

private slots:
    void fileOpen();
    void switchPages();
    void TypeChanged();
    void accept();
    void reject();
};
#endif // MAINWINDOW_H

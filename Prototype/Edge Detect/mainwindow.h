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
    enum Type {sobel, scharr, laplacian, canny};
    cv::Mat src, dst, x, y;
    void edgeDetect();

private:
    Ui::MainWindow *ui;
    MainWindow::Type type;

private slots:
    void TypeChanged();
    void accept();
    void reject();
};
#endif // MAINWINDOW_H

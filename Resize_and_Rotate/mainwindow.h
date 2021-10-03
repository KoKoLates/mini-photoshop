#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

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
    Mat image;
    void newCrop();

private:
    Ui::MainWindow *ui;
    Crop *crop;

signals:
    void cleanCrop();

private slots:
    void fileProcess();
    void switchPages();
    void accept();
    void reject();
};
#endif // MAINWINDOW_H

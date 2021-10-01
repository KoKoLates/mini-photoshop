#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "blur.h"
#include "sharpen.h"
#include "channel.h"
#include "colorspace.h"

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
    void newBlur();
    void newSharpen();
    void newChannel();
    void newColorSpace();

private:
    Ui::MainWindow *ui;
    Blur *blur;
    Sharpen *sharpen;
    Channel *channel;
    ColorSpace *colorM;

signals:
    void cleanBlur();
    void cleanChannel();
    void cleanSharpen();
    void cleanColorM();

private slots:
    void fileProcess();
    void switchPages();
    void accept();
    void reject();

protected:
    void dropEvent(QDropEvent*);
    void dragEnterEvent(QDragEnterEvent*);
};
#endif // MAINWINDOW_H

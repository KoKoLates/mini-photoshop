#ifndef DRAG_DROP_H
#define DRAG_DROP_H

#include <QMimeData>
#include <QDropEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDragEnterEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(true && image.empty())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl>urls = event->mimeData()->urls();
    if(urls.empty()) return;
    QString filePath = urls.first().toLocalFile();
    if(!filePath.isEmpty())
    {
        image = imread(filePath.toStdString().c_str());
        imshow("Image", image);
        emit ui->Size->triggered();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!image.empty())
    {
        QMessageBox::StandardButton reply
                = QMessageBox::question(this, "Photoshop", "The image hasn't been saved, \n sure to exit?",QMessageBox::Yes | QMessageBox::No );
        if(reply == QMessageBox::Yes)
        {
            image.release();
            destroyWindow("Image");
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
}

#endif // DRAG_DROP_H

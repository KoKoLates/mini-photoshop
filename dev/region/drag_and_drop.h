#ifndef DRAG_AND_DROP_H
#define DRAG_AND_DROP_H

#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>
#include "mainwindow.h"

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
    }
}

#endif // DRAG_AND_DROP_H

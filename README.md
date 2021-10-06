# Photoshop-Demo
Design a basic Photoshop demo programming with Qt IDE, OpenCV and some algorithms of images processing for exhibiting the results of 2021 summer course.

## Main Window
### Interface
### Pages Switch
```cpp
void MainWindow::switchPages()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->crop)
    {
        ...
    }
    eles if(action == ui->blur)
    {
        ...
    }
    else if(action == ui->sharpen)
    {
        ...
    }
    ...
}
```
Connect all the action signals to the `switchPages()` slots function, and using `qobject_cast` to find the action of sender, then switch to corresponding pages.
### Drag / Drop
```cpp
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(true && image.empty())
    {
        event->acceptProposedAction(); // accept to drag in the image
        ui->label->setStyleSheet("border: 5px dashed #242424");
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
        imshow("Image", image); //show on the Image window
        emit ui->Crop->triggered(); // switch to the crop pages as deflaut
    }
}
```
### Qss

## Resize
### Resize
### Rotate
### Crop

## Image
### Blur
### cvtColor
### Channel
### Sharpen

## Effect
### Color Effects
### Special Effects

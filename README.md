# Photoshop-Demo
Design a basic Photoshop demo programming with Qt IDE, OpenCV and some algorithms of images processing for exhibiting the results of 2021 summer course.

## Main Window
### Interface
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Images/console.png)
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Images/original.png)
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Images/preview.png) <br/><br/>
The console window is consist of workbench, image window and preview windows. The workbench can switch to different pages by triggering different action, and the effect of any function will dsiplay on the preview window as the preview for user to choose that using this method or not. By QDialogButton, ones could `cancel` the preview or `choose` this method and display the result on the image window and waiting for saving.

### Pages Switch
```cpp
void MainWindow::switchPages()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->crop)
    {
        ...
    }
    else if(action == ui->blur)
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
### [Drag / Drop](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Photoshop/event.h)
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
### [Resize](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Photoshop/resize.cpp)
```cpp
void Resize::valueChanged(int value)
{
    float percentage = (value + 20.0) / 20.0;
    int width = src.cols * percentage;
    int height = src.rows * percentage;
    cv::resize(src, temp, Size(width,height));
    imshow("Preview", temp);
}
```
Cooperate with QSlider to display the effects of resizing in the  preview windows.
### [Rotate](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Photoshop/rotate.cpp)
```cpp
void Rotate::rotate()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button == vertical) 
    {
        flip(dst, dst, 0); // for vertical rotate
    }
    else if(button == horizontal)
    {
        flip(dst, dst, 1); // for horizontal rotate
    }
    else if(button == counterclockwise)
    {
        transpose(dst, dst); // for counterclockwise rotate
        flip(dst, dst, 0);
    }
    else
    {
        transpose(dst, dst); // for clockwise rotate
        flip(dst, dst, 1);
    }
    imshow("Preview", dst);
}
```
### [Crop](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Photoshop/crop.cpp)

## Image
### Blur
### cvtColor
### Channel
### Sharpen

## Effect
### Color Effects
### Special Effects

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

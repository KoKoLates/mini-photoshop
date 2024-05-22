QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += C:\OpenCV-MinGW-Build\include
LIBS += C:\OpenCV-MinGW-Build\x64\mingw\bin\libopencv_core411.dll
LIBS += C:\OpenCV-MinGW-Build\x64\mingw\bin\libopencv_imgcodecs411.dll
LIBS += C:\OpenCV-MinGW-Build\x64\mingw\bin\libopencv_imgproc411.dll
LIBS += C:\OpenCV-MinGW-Build\x64\mingw\bin\libopencv_highgui411.dll
LIBS += C:\OpenCV-MinGW-Build\x64\mingw\bin\libopencv_videoio411.dll
LIBS += C:\OpenCV-MinGW-Build\x64\mingw\bin\libopencv_calib3d411.dll
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

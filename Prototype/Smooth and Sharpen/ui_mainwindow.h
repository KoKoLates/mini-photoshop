/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *open;
    QAction *save;
    QAction *smooth;
    QAction *sharpen;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QFormLayout *formLayout;
    QRadioButton *Bilateral;
    QRadioButton *Box;
    QRadioButton *Median;
    QRadioButton *Gaussian;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *blurKernel;
    QDialogButtonBox *blurCheck;
    QWidget *page_3;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QRadioButton *General;
    QRadioButton *Laplacian;
    QSlider *generalSlider;
    QSlider *laplacianSlider;
    QDialogButtonBox *sharpenCheck;
    QMenuBar *menubar;
    QMenu *file;
    QMenu *filter;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(331, 250);
        open = new QAction(MainWindow);
        open->setObjectName(QString::fromUtf8("open"));
        save = new QAction(MainWindow);
        save->setObjectName(QString::fromUtf8("save"));
        smooth = new QAction(MainWindow);
        smooth->setObjectName(QString::fromUtf8("smooth"));
        sharpen = new QAction(MainWindow);
        sharpen->setObjectName(QString::fromUtf8("sharpen"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QFont font;
        font.setFamily(QString::fromUtf8("Bahnschrift SemiLight"));
        centralwidget->setFont(font);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(9, 9, 313, 188));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayout = new QHBoxLayout(page);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_2 = new QHBoxLayout(page_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        Bilateral = new QRadioButton(widget);
        Bilateral->setObjectName(QString::fromUtf8("Bilateral"));

        formLayout->setWidget(5, QFormLayout::FieldRole, Bilateral);

        Box = new QRadioButton(widget);
        Box->setObjectName(QString::fromUtf8("Box"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Box);

        Median = new QRadioButton(widget);
        Median->setObjectName(QString::fromUtf8("Median"));

        formLayout->setWidget(1, QFormLayout::FieldRole, Median);

        Gaussian = new QRadioButton(widget);
        Gaussian->setObjectName(QString::fromUtf8("Gaussian"));

        formLayout->setWidget(5, QFormLayout::LabelRole, Gaussian);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(groupBox);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        blurKernel = new QSpinBox(widget_2);
        blurKernel->setObjectName(QString::fromUtf8("blurKernel"));

        horizontalLayout_3->addWidget(blurKernel);

        blurCheck = new QDialogButtonBox(widget_2);
        blurCheck->setObjectName(QString::fromUtf8("blurCheck"));
        blurCheck->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(blurCheck);


        verticalLayout_2->addWidget(widget_2);


        horizontalLayout_2->addWidget(groupBox);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        horizontalLayout_4 = new QHBoxLayout(page_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_2 = new QGroupBox(page_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        widget_4 = new QWidget(groupBox_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(30);
        gridLayout->setContentsMargins(15, -1, 15, -1);
        General = new QRadioButton(widget_3);
        General->setObjectName(QString::fromUtf8("General"));

        gridLayout->addWidget(General, 0, 0, 1, 1);

        Laplacian = new QRadioButton(widget_3);
        Laplacian->setObjectName(QString::fromUtf8("Laplacian"));

        gridLayout->addWidget(Laplacian, 1, 0, 1, 1);

        generalSlider = new QSlider(widget_3);
        generalSlider->setObjectName(QString::fromUtf8("generalSlider"));
        generalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(generalSlider, 0, 1, 1, 1);

        laplacianSlider = new QSlider(widget_3);
        laplacianSlider->setObjectName(QString::fromUtf8("laplacianSlider"));
        laplacianSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(laplacianSlider, 1, 1, 1, 1);


        verticalLayout->addWidget(widget_3);

        sharpenCheck = new QDialogButtonBox(widget_4);
        sharpenCheck->setObjectName(QString::fromUtf8("sharpenCheck"));
        sharpenCheck->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(sharpenCheck);


        horizontalLayout_5->addWidget(widget_4);


        horizontalLayout_4->addWidget(groupBox_2);

        stackedWidget->addWidget(page_3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 331, 21));
        file = new QMenu(menubar);
        file->setObjectName(QString::fromUtf8("file"));
        filter = new QMenu(menubar);
        filter->setObjectName(QString::fromUtf8("filter"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(file->menuAction());
        menubar->addAction(filter->menuAction());
        file->addAction(open);
        file->addAction(save);
        filter->addAction(smooth);
        filter->addAction(sharpen);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        open->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        smooth->setText(QCoreApplication::translate("MainWindow", "Smooth", nullptr));
        sharpen->setText(QCoreApplication::translate("MainWindow", "Sharpen", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Drag and Drop", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Blur", nullptr));
        Bilateral->setText(QCoreApplication::translate("MainWindow", "Bilateral", nullptr));
        Box->setText(QCoreApplication::translate("MainWindow", "Box Filter", nullptr));
        Median->setText(QCoreApplication::translate("MainWindow", "Median", nullptr));
        Gaussian->setText(QCoreApplication::translate("MainWindow", "Gaussian", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "kernel", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Sharpen", nullptr));
        General->setText(QCoreApplication::translate("MainWindow", "General", nullptr));
        Laplacian->setText(QCoreApplication::translate("MainWindow", "Laplacian", nullptr));
        file->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        filter->setTitle(QCoreApplication::translate("MainWindow", "Filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QFrame *line_2;
    QLabel *label;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QFrame *line_3;
    QSpacerItem *verticalSpacer;
    GLWidget *glwidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName("MainWindowClass");
        MainWindowClass->resize(2000, 1500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindowClass->sizePolicy().hasHeightForWidth());
        MainWindowClass->setSizePolicy(sizePolicy);
        MainWindowClass->setLocale(QLocale(QLocale::German, QLocale::Germany));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName("line_2");
        line_2->setLineWidth(1);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        label = new QLabel(centralWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        radioButton_1 = new QRadioButton(centralWidget);
        radioButton_1->setObjectName("radioButton_1");

        verticalLayout->addWidget(radioButton_1);

        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName("radioButton_2");

        verticalLayout->addWidget(radioButton_2);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName("line_3");
        line_3->setLineWidth(1);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        glwidget = new GLWidget(centralWidget);
        glwidget->setObjectName("glwidget");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(glwidget->sizePolicy().hasHeightForWidth());
        glwidget->setSizePolicy(sizePolicy1);
        glwidget->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(glwidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");

        horizontalLayout_2->addWidget(glwidget);

        MainWindowClass->setCentralWidget(centralWidget);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QCoreApplication::translate("MainWindowClass", "CompGeoTemplate", nullptr));
        label->setText(QCoreApplication::translate("MainWindowClass", "Algorithm Mode", nullptr));
#if QT_CONFIG(tooltip)
        radioButton_1->setToolTip(QCoreApplication::translate("MainWindowClass", "<html><head/><body><p><span style=\" font-weight:600;\">R.A. Jarvis (1973):</span> On the identification of the convex hull of a finite set of points in the plane. Information Processing Letters 2: 18\342\200\22321. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        radioButton_1->setText(QCoreApplication::translate("MainWindowClass", "Jarvis' March", nullptr));
#if QT_CONFIG(tooltip)
        radioButton_2->setToolTip(QCoreApplication::translate("MainWindowClass", "<html><head/><body><p><span style=\" font-weight:600;\">R. Graham (1972):</span> An Efficient Algorithm for Determining the Convex Hull of a Finite Planar Set, Info. Proc. Letters 1, 132-133.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        radioButton_2->setText(QCoreApplication::translate("MainWindowClass", "Graham's Scan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

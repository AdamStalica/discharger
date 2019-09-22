/********************************************************************************
** Form generated from reading UI file 'WgtSim.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTSIM_H
#define UI_WGTSIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtSim
{
public:
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QProgressBar *progressBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGroupBox *groupBox_3;

    void setupUi(QWidget *WgtSim)
    {
        if (WgtSim->objectName().isEmpty())
            WgtSim->setObjectName(QString::fromUtf8("WgtSim"));
        WgtSim->resize(1036, 744);
        groupBox = new QGroupBox(WgtSim);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(210, 170, 120, 80));
        groupBox_2 = new QGroupBox(WgtSim);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(69, 270, 261, 181));
        progressBar = new QProgressBar(groupBox_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 30, 118, 23));
        progressBar->setValue(24);
        dockWidget = new QDockWidget(WgtSim);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setGeometry(QRect(520, 120, 361, 351));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        groupBox_3 = new QGroupBox(dockWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 10, 300, 300));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(300, 300));
        dockWidget->setWidget(dockWidgetContents);

        retranslateUi(WgtSim);

        QMetaObject::connectSlotsByName(WgtSim);
    } // setupUi

    void retranslateUi(QWidget *WgtSim)
    {
        WgtSim->setWindowTitle(QCoreApplication::translate("WgtSim", "WgtSim", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WgtSim", "Current data", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WgtSim", "Control", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WgtSim", "Chart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtSim: public Ui_WgtSim {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTSIM_H

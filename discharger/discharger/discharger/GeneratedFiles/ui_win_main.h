/********************************************************************************
** Form generated from reading UI file 'win_main.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIN_MAIN_H
#define UI_WIN_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_win_mainClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *layout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *win_mainClass)
    {
        if (win_mainClass->objectName().isEmpty())
            win_mainClass->setObjectName(QString::fromUtf8("win_mainClass"));
        win_mainClass->resize(600, 400);
        centralWidget = new QWidget(win_mainClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        layout = new QVBoxLayout();
        layout->setSpacing(6);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setContentsMargins(0, -1, -1, -1);

        verticalLayout_2->addLayout(layout);

        win_mainClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(win_mainClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        win_mainClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(win_mainClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        win_mainClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(win_mainClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        win_mainClass->setStatusBar(statusBar);

        retranslateUi(win_mainClass);

        QMetaObject::connectSlotsByName(win_mainClass);
    } // setupUi

    void retranslateUi(QMainWindow *win_mainClass)
    {
        win_mainClass->setWindowTitle(QCoreApplication::translate("win_mainClass", "win_main", nullptr));
    } // retranslateUi

};

namespace Ui {
    class win_mainClass: public Ui_win_mainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIN_MAIN_H

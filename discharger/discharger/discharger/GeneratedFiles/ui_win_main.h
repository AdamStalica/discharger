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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_win_mainClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *win_mainClass)
    {
        if (win_mainClass->objectName().isEmpty())
            win_mainClass->setObjectName(QString::fromUtf8("win_mainClass"));
        win_mainClass->resize(600, 400);
        menuBar = new QMenuBar(win_mainClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        win_mainClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(win_mainClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        win_mainClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(win_mainClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        win_mainClass->setCentralWidget(centralWidget);
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

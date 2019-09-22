/********************************************************************************
** Form generated from reading UI file 'win_main.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIN_MAIN_H
#define UI_WIN_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_win_mainClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QScrollArea *mainArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menuOption;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *win_mainClass)
    {
        if (win_mainClass->objectName().isEmpty())
            win_mainClass->setObjectName(QString::fromUtf8("win_mainClass"));
        win_mainClass->resize(994, 766);
        centralWidget = new QWidget(win_mainClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainArea = new QScrollArea(centralWidget);
        mainArea->setObjectName(QString::fromUtf8("mainArea"));
        mainArea->setWidgetResizable(true);
        mainArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 974, 693));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        mainArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(mainArea, 0, 0, 1, 1);

        win_mainClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(win_mainClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 994, 21));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QString::fromUtf8("menuOption"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        win_mainClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(win_mainClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        win_mainClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(win_mainClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        win_mainClass->setStatusBar(statusBar);

        menuBar->addAction(menuOption->menuAction());
        menuBar->addAction(menuHelp->menuAction());

        retranslateUi(win_mainClass);

        QMetaObject::connectSlotsByName(win_mainClass);
    } // setupUi

    void retranslateUi(QMainWindow *win_mainClass)
    {
        win_mainClass->setWindowTitle(QCoreApplication::translate("win_mainClass", "win_main", nullptr));
        menuOption->setTitle(QCoreApplication::translate("win_mainClass", "Option", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("win_mainClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class win_mainClass: public Ui_win_mainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIN_MAIN_H

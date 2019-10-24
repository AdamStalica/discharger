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
#include <QtGui/QIcon>
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
    QAction *actionHelp;
    QAction *actionAbout_program;
    QAction *actionReload_CSS;
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
        QIcon icon;
        icon.addFile(QString::fromUtf8("media/discharger.ico"), QSize(), QIcon::Normal, QIcon::Off);
        win_mainClass->setWindowIcon(icon);
        actionHelp = new QAction(win_mainClass);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout_program = new QAction(win_mainClass);
        actionAbout_program->setObjectName(QString::fromUtf8("actionAbout_program"));
        actionReload_CSS = new QAction(win_mainClass);
        actionReload_CSS->setObjectName(QString::fromUtf8("actionReload_CSS"));
        centralWidget = new QWidget(win_mainClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        mainArea = new QScrollArea(centralWidget);
        mainArea->setObjectName(QString::fromUtf8("mainArea"));
        mainArea->setWidgetResizable(true);
        mainArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 992, 711));
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
        menuOption->addAction(actionReload_CSS);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionAbout_program);

        retranslateUi(win_mainClass);

        QMetaObject::connectSlotsByName(win_mainClass);
    } // setupUi

    void retranslateUi(QMainWindow *win_mainClass)
    {
        win_mainClass->setWindowTitle(QCoreApplication::translate("win_mainClass", "Discharger", nullptr));
        actionHelp->setText(QCoreApplication::translate("win_mainClass", "Help", nullptr));
#if QT_CONFIG(shortcut)
        actionHelp->setShortcut(QCoreApplication::translate("win_mainClass", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout_program->setText(QCoreApplication::translate("win_mainClass", "About program", nullptr));
        actionReload_CSS->setText(QCoreApplication::translate("win_mainClass", "Reload CSS", nullptr));
#if QT_CONFIG(shortcut)
        actionReload_CSS->setShortcut(QCoreApplication::translate("win_mainClass", "F7", nullptr));
#endif // QT_CONFIG(shortcut)
        menuOption->setTitle(QCoreApplication::translate("win_mainClass", "Option", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("win_mainClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class win_mainClass: public Ui_win_mainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIN_MAIN_H

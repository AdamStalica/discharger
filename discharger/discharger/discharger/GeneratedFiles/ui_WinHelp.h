/********************************************************************************
** Form generated from reading UI file 'WinHelp.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINHELP_H
#define UI_WINHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinHelp
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *WinHelp)
    {
        if (WinHelp->objectName().isEmpty())
            WinHelp->setObjectName(QString::fromUtf8("WinHelp"));
        WinHelp->resize(484, 378);
        verticalLayout_2 = new QVBoxLayout(WinHelp);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(WinHelp);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 482, 376));
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8("border: 0;"));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(scrollAreaWidgetContents);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(WinHelp);

        QMetaObject::connectSlotsByName(WinHelp);
    } // setupUi

    void retranslateUi(QWidget *WinHelp)
    {
        WinHelp->setWindowTitle(QCoreApplication::translate("WinHelp", "Discharger Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinHelp: public Ui_WinHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINHELP_H

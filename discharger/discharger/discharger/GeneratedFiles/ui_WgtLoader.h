/********************************************************************************
** Form generated from reading UI file 'WgtLoader.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTLOADER_H
#define UI_WGTLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtLoader
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *mv_lbl;
    QLabel *comment_lbl;

    void setupUi(QWidget *WgtLoader)
    {
        if (WgtLoader->objectName().isEmpty())
            WgtLoader->setObjectName(QString::fromUtf8("WgtLoader"));
        WgtLoader->resize(429, 356);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtLoader->sizePolicy().hasHeightForWidth());
        WgtLoader->setSizePolicy(sizePolicy);
        WgtLoader->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(WgtLoader);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(WgtLoader);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(200, 0));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgba(80, 165, 30, 0.5);border-radius:10px;"));
        groupBox->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 20, -1, 20);
        mv_lbl = new QLabel(groupBox);
        mv_lbl->setObjectName(QString::fromUtf8("mv_lbl"));
        sizePolicy1.setHeightForWidth(mv_lbl->sizePolicy().hasHeightForWidth());
        mv_lbl->setSizePolicy(sizePolicy1);
        mv_lbl->setMinimumSize(QSize(100, 100));
        mv_lbl->setAutoFillBackground(false);
        mv_lbl->setStyleSheet(QString::fromUtf8("background-color: white; border-radius: 10px;"));
        mv_lbl->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(mv_lbl, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        comment_lbl = new QLabel(groupBox);
        comment_lbl->setObjectName(QString::fromUtf8("comment_lbl"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comment_lbl->sizePolicy().hasHeightForWidth());
        comment_lbl->setSizePolicy(sizePolicy2);
        comment_lbl->setStyleSheet(QString::fromUtf8("background-color:white;"));
        comment_lbl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        comment_lbl->setMargin(10);

        verticalLayout_2->addWidget(comment_lbl, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(groupBox, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        retranslateUi(WgtLoader);

        QMetaObject::connectSlotsByName(WgtLoader);
    } // setupUi

    void retranslateUi(QWidget *WgtLoader)
    {
        WgtLoader->setWindowTitle(QCoreApplication::translate("WgtLoader", "WgtLoader", nullptr));
        groupBox->setTitle(QString());
        mv_lbl->setText(QCoreApplication::translate("WgtLoader", "Loading", nullptr));
        comment_lbl->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WgtLoader: public Ui_WgtLoader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTLOADER_H

/********************************************************************************
** Form generated from reading UI file 'WgtNewSpeedway.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTNEWSPEEDWAY_H
#define UI_WGTNEWSPEEDWAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtNewSpeedway
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *sp_lbl;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *sp_cnl_btn;
    QPushButton *sp_add_btn;
    QLineEdit *name;
    QLineEdit *longitude;
    QLineEdit *longitude_toler;
    QLineEdit *latitude;
    QLineEdit *latitude_toler;

    void setupUi(QWidget *WgtNewSpeedway)
    {
        if (WgtNewSpeedway->objectName().isEmpty())
            WgtNewSpeedway->setObjectName(QString::fromUtf8("WgtNewSpeedway"));
        WgtNewSpeedway->resize(500, 259);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtNewSpeedway->sizePolicy().hasHeightForWidth());
        WgtNewSpeedway->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(WgtNewSpeedway);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 0, -1);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(WgtNewSpeedway);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(0, 50));
        label_2->setLineWidth(1);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        label_4 = new QLabel(WgtNewSpeedway);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMaximumSize(QSize(16777215, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        sp_lbl = new QLabel(WgtNewSpeedway);
        sp_lbl->setObjectName(QString::fromUtf8("sp_lbl"));
        sizePolicy1.setHeightForWidth(sp_lbl->sizePolicy().hasHeightForWidth());
        sp_lbl->setSizePolicy(sizePolicy1);
        sp_lbl->setMaximumSize(QSize(16777215, 20));
        sp_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(sp_lbl, 6, 0, 1, 2);

        label_5 = new QLabel(WgtNewSpeedway);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMaximumSize(QSize(16777215, 16777215));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_3 = new QLabel(WgtNewSpeedway);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMaximumSize(QSize(16777215, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_6 = new QLabel(WgtNewSpeedway);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setMaximumSize(QSize(16777215, 16777215));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label = new QLabel(WgtNewSpeedway);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(16777215, 16777215));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        sp_cnl_btn = new QPushButton(WgtNewSpeedway);
        sp_cnl_btn->setObjectName(QString::fromUtf8("sp_cnl_btn"));

        horizontalLayout->addWidget(sp_cnl_btn);

        sp_add_btn = new QPushButton(WgtNewSpeedway);
        sp_add_btn->setObjectName(QString::fromUtf8("sp_add_btn"));

        horizontalLayout->addWidget(sp_add_btn);


        gridLayout->addLayout(horizontalLayout, 7, 0, 1, 2);

        name = new QLineEdit(WgtNewSpeedway);
        name->setObjectName(QString::fromUtf8("name"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy3);
        name->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(name, 1, 1, 1, 1);

        longitude = new QLineEdit(WgtNewSpeedway);
        longitude->setObjectName(QString::fromUtf8("longitude"));
        sizePolicy3.setHeightForWidth(longitude->sizePolicy().hasHeightForWidth());
        longitude->setSizePolicy(sizePolicy3);
        longitude->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(longitude, 2, 1, 1, 1);

        longitude_toler = new QLineEdit(WgtNewSpeedway);
        longitude_toler->setObjectName(QString::fromUtf8("longitude_toler"));

        gridLayout->addWidget(longitude_toler, 3, 1, 1, 1);

        latitude = new QLineEdit(WgtNewSpeedway);
        latitude->setObjectName(QString::fromUtf8("latitude"));

        gridLayout->addWidget(latitude, 4, 1, 1, 1);

        latitude_toler = new QLineEdit(WgtNewSpeedway);
        latitude_toler->setObjectName(QString::fromUtf8("latitude_toler"));

        gridLayout->addWidget(latitude_toler, 5, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(WgtNewSpeedway);

        QMetaObject::connectSlotsByName(WgtNewSpeedway);
    } // setupUi

    void retranslateUi(QWidget *WgtNewSpeedway)
    {
        WgtNewSpeedway->setWindowTitle(QCoreApplication::translate("WgtNewSpeedway", "WgtNewSpeedway", nullptr));
        label_2->setText(QCoreApplication::translate("WgtNewSpeedway", "New speedway", nullptr));
        label_4->setText(QCoreApplication::translate("WgtNewSpeedway", "Longitude tolerance: ", nullptr));
        sp_lbl->setText(QString());
        label_5->setText(QCoreApplication::translate("WgtNewSpeedway", "Latitude: ", nullptr));
        label_3->setText(QCoreApplication::translate("WgtNewSpeedway", "Longitude: ", nullptr));
        label_6->setText(QCoreApplication::translate("WgtNewSpeedway", "Latitude tolerance: ", nullptr));
        label->setText(QCoreApplication::translate("WgtNewSpeedway", "Name: ", nullptr));
        sp_cnl_btn->setText(QCoreApplication::translate("WgtNewSpeedway", "Cancel", nullptr));
        sp_add_btn->setText(QCoreApplication::translate("WgtNewSpeedway", "Add speedway", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtNewSpeedway: public Ui_WgtNewSpeedway {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTNEWSPEEDWAY_H

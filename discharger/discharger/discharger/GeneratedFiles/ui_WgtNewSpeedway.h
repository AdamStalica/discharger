/********************************************************************************
** Form generated from reading UI file 'WgtNewSpeedway.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
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
    QLineEdit *longitude;
    QLineEdit *latitude;
    QLabel *label_4;
    QLabel *sp_lbl;
    QLineEdit *longitude_toler;
    QLabel *label_5;
    QLineEdit *name;
    QLabel *label_3;
    QLabel *label_6;
    QLineEdit *latitude_toler;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *sp_cnl_btn;
    QPushButton *sp_add_btn;

    void setupUi(QWidget *WgtNewSpeedway)
    {
        if (WgtNewSpeedway->objectName().isEmpty())
            WgtNewSpeedway->setObjectName(QString::fromUtf8("WgtNewSpeedway"));
        WgtNewSpeedway->resize(380, 260);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtNewSpeedway->sizePolicy().hasHeightForWidth());
        WgtNewSpeedway->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(WgtNewSpeedway);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
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

        longitude = new QLineEdit(WgtNewSpeedway);
        longitude->setObjectName(QString::fromUtf8("longitude"));

        gridLayout->addWidget(longitude, 2, 1, 1, 1);

        latitude = new QLineEdit(WgtNewSpeedway);
        latitude->setObjectName(QString::fromUtf8("latitude"));

        gridLayout->addWidget(latitude, 4, 1, 1, 1);

        label_4 = new QLabel(WgtNewSpeedway);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMaximumSize(QSize(150, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        sp_lbl = new QLabel(WgtNewSpeedway);
        sp_lbl->setObjectName(QString::fromUtf8("sp_lbl"));
        sp_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(sp_lbl, 6, 0, 1, 2);

        longitude_toler = new QLineEdit(WgtNewSpeedway);
        longitude_toler->setObjectName(QString::fromUtf8("longitude_toler"));

        gridLayout->addWidget(longitude_toler, 3, 1, 1, 1);

        label_5 = new QLabel(WgtNewSpeedway);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMaximumSize(QSize(150, 16777215));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        name = new QLineEdit(WgtNewSpeedway);
        name->setObjectName(QString::fromUtf8("name"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy3);
        name->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(name, 1, 1, 1, 1);

        label_3 = new QLabel(WgtNewSpeedway);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMaximumSize(QSize(150, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_6 = new QLabel(WgtNewSpeedway);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setMaximumSize(QSize(150, 16777215));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        latitude_toler = new QLineEdit(WgtNewSpeedway);
        latitude_toler->setObjectName(QString::fromUtf8("latitude_toler"));

        gridLayout->addWidget(latitude_toler, 5, 1, 1, 1);

        label = new QLabel(WgtNewSpeedway);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy4);
        label->setMinimumSize(QSize(150, 0));
        label->setMaximumSize(QSize(500, 16777215));
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
        name->setInputMask(QString());
        label_3->setText(QCoreApplication::translate("WgtNewSpeedway", "Longitude: ", nullptr));
        label_6->setText(QCoreApplication::translate("WgtNewSpeedway", "Latitude tolerance: ", nullptr));
        latitude_toler->setInputMask(QString());
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

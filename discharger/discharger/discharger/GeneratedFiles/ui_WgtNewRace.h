/********************************************************************************
** Form generated from reading UI file 'WgtNewRace.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTNEWRACE_H
#define UI_WGTNEWRACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtNewRace
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *race_lbl;
    QLabel *label_3;
    QDateEdit *race_date;
    QLabel *label_2;
    QLineEdit *sp_name;
    QLineEdit *name;
    QLabel *label_6;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *race_cnl_btn;
    QPushButton *race_add_btn;

    void setupUi(QWidget *WgtNewRace)
    {
        if (WgtNewRace->objectName().isEmpty())
            WgtNewRace->setObjectName(QString::fromUtf8("WgtNewRace"));
        WgtNewRace->resize(500, 210);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtNewRace->sizePolicy().hasHeightForWidth());
        WgtNewRace->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(WgtNewRace);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 0, -1);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        race_lbl = new QLabel(WgtNewRace);
        race_lbl->setObjectName(QString::fromUtf8("race_lbl"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(race_lbl->sizePolicy().hasHeightForWidth());
        race_lbl->setSizePolicy(sizePolicy1);
        race_lbl->setMinimumSize(QSize(0, 20));
        race_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(race_lbl, 4, 0, 1, 2);

        label_3 = new QLabel(WgtNewRace);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        race_date = new QDateEdit(WgtNewRace);
        race_date->setObjectName(QString::fromUtf8("race_date"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(race_date->sizePolicy().hasHeightForWidth());
        race_date->setSizePolicy(sizePolicy3);
        race_date->setMinimumSize(QSize(80, 0));

        gridLayout->addWidget(race_date, 2, 1, 1, 1);

        label_2 = new QLabel(WgtNewRace);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMaximumSize(QSize(16777215, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        sp_name = new QLineEdit(WgtNewRace);
        sp_name->setObjectName(QString::fromUtf8("sp_name"));
        sp_name->setEnabled(false);
        sizePolicy3.setHeightForWidth(sp_name->sizePolicy().hasHeightForWidth());
        sp_name->setSizePolicy(sizePolicy3);
        sp_name->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(sp_name, 1, 1, 1, 1);

        name = new QLineEdit(WgtNewRace);
        name->setObjectName(QString::fromUtf8("name"));

        gridLayout->addWidget(name, 3, 1, 1, 1);

        label_6 = new QLabel(WgtNewRace);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(0, 50));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 0, 0, 1, 2);

        label = new QLabel(WgtNewRace);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        race_cnl_btn = new QPushButton(WgtNewRace);
        race_cnl_btn->setObjectName(QString::fromUtf8("race_cnl_btn"));

        horizontalLayout->addWidget(race_cnl_btn);

        race_add_btn = new QPushButton(WgtNewRace);
        race_add_btn->setObjectName(QString::fromUtf8("race_add_btn"));

        horizontalLayout->addWidget(race_add_btn);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(WgtNewRace);

        QMetaObject::connectSlotsByName(WgtNewRace);
    } // setupUi

    void retranslateUi(QWidget *WgtNewRace)
    {
        WgtNewRace->setWindowTitle(QCoreApplication::translate("WgtNewRace", "WgtNewRace", nullptr));
        race_lbl->setText(QString());
        label_3->setText(QCoreApplication::translate("WgtNewRace", "Speedway name: ", nullptr));
        label_2->setText(QCoreApplication::translate("WgtNewRace", "Name: ", nullptr));
        sp_name->setText(QString());
        label_6->setText(QCoreApplication::translate("WgtNewRace", "New race", nullptr));
        label->setText(QCoreApplication::translate("WgtNewRace", "Race date: ", nullptr));
        race_cnl_btn->setText(QCoreApplication::translate("WgtNewRace", "Cancel", nullptr));
        race_add_btn->setText(QCoreApplication::translate("WgtNewRace", "Add race", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtNewRace: public Ui_WgtNewRace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTNEWRACE_H

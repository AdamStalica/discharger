/********************************************************************************
** Form generated from reading UI file 'WgtImport.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTIMPORT_H
#define UI_WGTIMPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtImport
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *sp_box;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *sp_lay;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *sp_list;
    QPushButton *sp_btn;
    QGroupBox *race_box;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *race_list;
    QPushButton *race_btn;
    QGroupBox *lg_box;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout;
    QComboBox *lg_batt_l_list;
    QLabel *label_3;
    QComboBox *lg_types_list;
    QComboBox *lg_batt_r_list;
    QLabel *label_4;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *lg_fp_ln;
    QPushButton *lg_fp_btn;

    void setupUi(QWidget *WgtImport)
    {
        if (WgtImport->objectName().isEmpty())
            WgtImport->setObjectName(QString::fromUtf8("WgtImport"));
        WgtImport->resize(500, 489);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtImport->sizePolicy().hasHeightForWidth());
        WgtImport->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(WgtImport);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox_3 = new QGroupBox(WgtImport);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setMinimumSize(QSize(450, 0));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        sp_box = new QGroupBox(groupBox_3);
        sp_box->setObjectName(QString::fromUtf8("sp_box"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sp_box->sizePolicy().hasHeightForWidth());
        sp_box->setSizePolicy(sizePolicy2);
        sp_box->setMinimumSize(QSize(0, 0));
        sp_box->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(sp_box);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        sp_lay = new QVBoxLayout();
        sp_lay->setSpacing(6);
        sp_lay->setObjectName(QString::fromUtf8("sp_lay"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(sp_box);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        sp_list = new QComboBox(sp_box);
        sp_list->setObjectName(QString::fromUtf8("sp_list"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sp_list->sizePolicy().hasHeightForWidth());
        sp_list->setSizePolicy(sizePolicy3);
        sp_list->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(sp_list);


        sp_lay->addLayout(horizontalLayout);

        sp_btn = new QPushButton(sp_box);
        sp_btn->setObjectName(QString::fromUtf8("sp_btn"));
        sizePolicy3.setHeightForWidth(sp_btn->sizePolicy().hasHeightForWidth());
        sp_btn->setSizePolicy(sizePolicy3);
        sp_btn->setMinimumSize(QSize(150, 0));
        sp_btn->setMaximumSize(QSize(150, 16777215));
        sp_btn->setLayoutDirection(Qt::LeftToRight);

        sp_lay->addWidget(sp_btn, 0, Qt::AlignRight);


        verticalLayout->addLayout(sp_lay);


        verticalLayout_5->addWidget(sp_box);

        race_box = new QGroupBox(groupBox_3);
        race_box->setObjectName(QString::fromUtf8("race_box"));
        race_box->setEnabled(true);
        sizePolicy2.setHeightForWidth(race_box->sizePolicy().hasHeightForWidth());
        race_box->setSizePolicy(sizePolicy2);
        race_box->setMinimumSize(QSize(460, 0));
        verticalLayout_3 = new QVBoxLayout(race_box);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(race_box);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        race_list = new QComboBox(race_box);
        race_list->setObjectName(QString::fromUtf8("race_list"));
        sizePolicy3.setHeightForWidth(race_list->sizePolicy().hasHeightForWidth());
        race_list->setSizePolicy(sizePolicy3);
        race_list->setMinimumSize(QSize(300, 0));

        horizontalLayout_2->addWidget(race_list);


        verticalLayout_2->addLayout(horizontalLayout_2);

        race_btn = new QPushButton(race_box);
        race_btn->setObjectName(QString::fromUtf8("race_btn"));
        sizePolicy3.setHeightForWidth(race_btn->sizePolicy().hasHeightForWidth());
        race_btn->setSizePolicy(sizePolicy3);
        race_btn->setMinimumSize(QSize(150, 0));

        verticalLayout_2->addWidget(race_btn, 0, Qt::AlignRight);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_5->addWidget(race_box);

        lg_box = new QGroupBox(groupBox_3);
        lg_box->setObjectName(QString::fromUtf8("lg_box"));
        lg_box->setEnabled(true);
        sizePolicy2.setHeightForWidth(lg_box->sizePolicy().hasHeightForWidth());
        lg_box->setSizePolicy(sizePolicy2);
        verticalLayout_6 = new QVBoxLayout(lg_box);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lg_batt_l_list = new QComboBox(lg_box);
        lg_batt_l_list->setObjectName(QString::fromUtf8("lg_batt_l_list"));

        gridLayout->addWidget(lg_batt_l_list, 1, 1, 1, 1);

        label_3 = new QLabel(lg_box);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lg_types_list = new QComboBox(lg_box);
        lg_types_list->setObjectName(QString::fromUtf8("lg_types_list"));
        sizePolicy3.setHeightForWidth(lg_types_list->sizePolicy().hasHeightForWidth());
        lg_types_list->setSizePolicy(sizePolicy3);
        lg_types_list->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(lg_types_list, 0, 1, 1, 1);

        lg_batt_r_list = new QComboBox(lg_box);
        lg_batt_r_list->setObjectName(QString::fromUtf8("lg_batt_r_list"));

        gridLayout->addWidget(lg_batt_r_list, 2, 1, 1, 1);

        label_4 = new QLabel(lg_box);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(lg_box);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(lg_box);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy4);
        label_6->setMinimumSize(QSize(120, 60));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_6);

        lg_fp_ln = new QLineEdit(lg_box);
        lg_fp_ln->setObjectName(QString::fromUtf8("lg_fp_ln"));
        sizePolicy3.setHeightForWidth(lg_fp_ln->sizePolicy().hasHeightForWidth());
        lg_fp_ln->setSizePolicy(sizePolicy3);
        lg_fp_ln->setMinimumSize(QSize(219, 0));

        horizontalLayout_3->addWidget(lg_fp_ln);

        lg_fp_btn = new QPushButton(lg_box);
        lg_fp_btn->setObjectName(QString::fromUtf8("lg_fp_btn"));
        sizePolicy3.setHeightForWidth(lg_fp_btn->sizePolicy().hasHeightForWidth());
        lg_fp_btn->setSizePolicy(sizePolicy3);
        lg_fp_btn->setMinimumSize(QSize(70, 0));

        horizontalLayout_3->addWidget(lg_fp_btn);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 2);


        verticalLayout_6->addLayout(gridLayout);


        verticalLayout_5->addWidget(lg_box);


        verticalLayout_4->addWidget(groupBox_3);


        retranslateUi(WgtImport);

        QMetaObject::connectSlotsByName(WgtImport);
    } // setupUi

    void retranslateUi(QWidget *WgtImport)
    {
        WgtImport->setWindowTitle(QCoreApplication::translate("WgtImport", "WgtImport", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WgtImport", "Import logs into the Data Base", nullptr));
        sp_box->setTitle(QCoreApplication::translate("WgtImport", "Speedway", nullptr));
        label->setText(QCoreApplication::translate("WgtImport", "Select speedway: ", nullptr));
        sp_btn->setText(QCoreApplication::translate("WgtImport", "New speedway", nullptr));
        race_box->setTitle(QCoreApplication::translate("WgtImport", "Race", nullptr));
        label_2->setText(QCoreApplication::translate("WgtImport", "Select race: ", nullptr));
        race_btn->setText(QCoreApplication::translate("WgtImport", "New race", nullptr));
        lg_box->setTitle(QCoreApplication::translate("WgtImport", "Logs", nullptr));
        label_3->setText(QCoreApplication::translate("WgtImport", "Log type: ", nullptr));
        label_4->setText(QCoreApplication::translate("WgtImport", "Left battery: ", nullptr));
        label_5->setText(QCoreApplication::translate("WgtImport", "Right battery: ", nullptr));
        label_6->setText(QCoreApplication::translate("WgtImport", "Choose log file: ", nullptr));
        lg_fp_btn->setText(QCoreApplication::translate("WgtImport", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtImport: public Ui_WgtImport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTIMPORT_H

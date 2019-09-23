/********************************************************************************
** Form generated from reading UI file 'WgtSim.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTSIM_H
#define UI_WGTSIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtSim
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *vol_chart_box;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_5;
    QPushButton *back_btn;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *start_stop_btn;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_13;
    QLabel *sim_stat_lbl;
    QLabel *label_17;
    QProgressBar *sim_progress_bar;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_18;
    QLineEdit *set_temp_ln;
    QLabel *label_19;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *est_time_lbl;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QLabel *sim_time_lbl;
    QHBoxLayout *horizontalLayout_7;
    QLabel *set_curr_lbl;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_7;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *current_lbl;
    QLabel *label_6;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLabel *vol_left_lbl;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_14;
    QLabel *temp_left_lbl;
    QLabel *label_15;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLabel *vol_right_lbl;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QLabel *temp_right_lbl;
    QLabel *label_12;
    QLabel *label;
    QGroupBox *curr_chart_box;

    void setupUi(QWidget *WgtSim)
    {
        if (WgtSim->objectName().isEmpty())
            WgtSim->setObjectName(QString::fromUtf8("WgtSim"));
        WgtSim->resize(819, 914);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtSim->sizePolicy().hasHeightForWidth());
        WgtSim->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(WgtSim);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        vol_chart_box = new QGroupBox(WgtSim);
        vol_chart_box->setObjectName(QString::fromUtf8("vol_chart_box"));
        vol_chart_box->setStyleSheet(QString::fromUtf8("background-color: yellow;"));

        gridLayout_2->addWidget(vol_chart_box, 1, 1, 1, 1);

        groupBox_5 = new QGroupBox(WgtSim);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        groupBox_5->setMinimumSize(QSize(315, 660));
        groupBox_5->setMaximumSize(QSize(315, 660));
        verticalLayout_5 = new QVBoxLayout(groupBox_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        back_btn = new QPushButton(groupBox_5);
        back_btn->setObjectName(QString::fromUtf8("back_btn"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(back_btn->sizePolicy().hasHeightForWidth());
        back_btn->setSizePolicy(sizePolicy2);
        back_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_5->addWidget(back_btn);

        groupBox_2 = new QGroupBox(groupBox_5);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        start_stop_btn = new QPushButton(groupBox_2);
        start_stop_btn->setObjectName(QString::fromUtf8("start_stop_btn"));
        sizePolicy2.setHeightForWidth(start_stop_btn->sizePolicy().hasHeightForWidth());
        start_stop_btn->setSizePolicy(sizePolicy2);
        start_stop_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_4->addWidget(start_stop_btn, 0, Qt::AlignHCenter);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(label_13);

        sim_stat_lbl = new QLabel(groupBox_2);
        sim_stat_lbl->setObjectName(QString::fromUtf8("sim_stat_lbl"));
        sizePolicy.setHeightForWidth(sim_stat_lbl->sizePolicy().hasHeightForWidth());
        sim_stat_lbl->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(sim_stat_lbl);


        verticalLayout_4->addLayout(horizontalLayout_8);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        verticalLayout_4->addWidget(label_17);

        sim_progress_bar = new QProgressBar(groupBox_2);
        sim_progress_bar->setObjectName(QString::fromUtf8("sim_progress_bar"));
        sim_progress_bar->setValue(24);

        verticalLayout_4->addWidget(sim_progress_bar);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        groupBox_3->setMinimumSize(QSize(0, 51));
        groupBox_3->setMaximumSize(QSize(16777215, 51));
        horizontalLayout_9 = new QHBoxLayout(groupBox_3);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_9->addWidget(label_18);

        set_temp_ln = new QLineEdit(groupBox_3);
        set_temp_ln->setObjectName(QString::fromUtf8("set_temp_ln"));

        horizontalLayout_9->addWidget(set_temp_ln);

        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_9->addWidget(label_19);


        verticalLayout_5->addWidget(groupBox_3);

        groupBox = new QGroupBox(groupBox_5);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1, Qt::AlignLeft);

        est_time_lbl = new QLabel(groupBox);
        est_time_lbl->setObjectName(QString::fromUtf8("est_time_lbl"));
        sizePolicy.setHeightForWidth(est_time_lbl->sizePolicy().hasHeightForWidth());
        est_time_lbl->setSizePolicy(sizePolicy);

        gridLayout->addWidget(est_time_lbl, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 5, 0, 1, 1);

        sim_time_lbl = new QLabel(groupBox);
        sim_time_lbl->setObjectName(QString::fromUtf8("sim_time_lbl"));
        sizePolicy.setHeightForWidth(sim_time_lbl->sizePolicy().hasHeightForWidth());
        sim_time_lbl->setSizePolicy(sizePolicy);

        gridLayout->addWidget(sim_time_lbl, 0, 1, 1, 1, Qt::AlignLeft);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        set_curr_lbl = new QLabel(groupBox);
        set_curr_lbl->setObjectName(QString::fromUtf8("set_curr_lbl"));
        sizePolicy.setHeightForWidth(set_curr_lbl->sizePolicy().hasHeightForWidth());
        set_curr_lbl->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(set_curr_lbl, 0, Qt::AlignLeft);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(label_16);


        gridLayout->addLayout(horizontalLayout_7, 4, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy4);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 4, 0, 1, 1, Qt::AlignLeft);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy5);
        groupBox_4->setMinimumSize(QSize(270, 230));
        groupBox_4->setMaximumSize(QSize(270, 230));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_4, 0, Qt::AlignRight);

        current_lbl = new QLabel(groupBox_4);
        current_lbl->setObjectName(QString::fromUtf8("current_lbl"));
        sizePolicy.setHeightForWidth(current_lbl->sizePolicy().hasHeightForWidth());
        current_lbl->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(current_lbl, 0, Qt::AlignLeft);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_6, 0, Qt::AlignLeft);


        verticalLayout->addLayout(horizontalLayout);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(50);
        sizePolicy6.setVerticalStretch(15);
        sizePolicy6.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy6);
        label_3->setMinimumSize(QSize(250, 120));
        label_3->setMaximumSize(QSize(250, 120));
        label_3->setSizeIncrement(QSize(50, 100));
        label_3->setBaseSize(QSize(50, 100));
        label_3->setPixmap(QPixmap(QString::fromUtf8("media/schem.png")));
        label_3->setScaledContents(true);

        verticalLayout->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_5);

        vol_left_lbl = new QLabel(groupBox_4);
        vol_left_lbl->setObjectName(QString::fromUtf8("vol_left_lbl"));
        sizePolicy.setHeightForWidth(vol_left_lbl->sizePolicy().hasHeightForWidth());
        vol_left_lbl->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(vol_left_lbl);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_8);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_14);

        temp_left_lbl = new QLabel(groupBox_4);
        temp_left_lbl->setObjectName(QString::fromUtf8("temp_left_lbl"));
        sizePolicy.setHeightForWidth(temp_left_lbl->sizePolicy().hasHeightForWidth());
        temp_left_lbl->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(temp_left_lbl);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_15);


        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(15, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_4->addItem(verticalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_9);

        vol_right_lbl = new QLabel(groupBox_4);
        vol_right_lbl->setObjectName(QString::fromUtf8("vol_right_lbl"));
        sizePolicy.setHeightForWidth(vol_right_lbl->sizePolicy().hasHeightForWidth());
        vol_right_lbl->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(vol_right_lbl);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_11);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_10);

        temp_right_lbl = new QLabel(groupBox_4);
        temp_right_lbl->setObjectName(QString::fromUtf8("temp_right_lbl"));
        sizePolicy.setHeightForWidth(temp_right_lbl->sizePolicy().hasHeightForWidth());
        temp_right_lbl->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(temp_right_lbl);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_12);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addWidget(groupBox_4, 6, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox);


        gridLayout_2->addWidget(groupBox_5, 0, 0, 2, 1);

        curr_chart_box = new QGroupBox(WgtSim);
        curr_chart_box->setObjectName(QString::fromUtf8("curr_chart_box"));
        curr_chart_box->setStyleSheet(QString::fromUtf8("background-color: blue;"));

        gridLayout_2->addWidget(curr_chart_box, 0, 1, 1, 1);


        retranslateUi(WgtSim);

        QMetaObject::connectSlotsByName(WgtSim);
    } // setupUi

    void retranslateUi(QWidget *WgtSim)
    {
        WgtSim->setWindowTitle(QCoreApplication::translate("WgtSim", "WgtSim", nullptr));
        vol_chart_box->setTitle(QCoreApplication::translate("WgtSim", "Voltage chart", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("WgtSim", "Data and Control", nullptr));
        back_btn->setText(QCoreApplication::translate("WgtSim", "Go back", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WgtSim", "Control", nullptr));
        start_stop_btn->setText(QCoreApplication::translate("WgtSim", "Start", nullptr));
        label_13->setText(QCoreApplication::translate("WgtSim", "Simulation status: ", nullptr));
        sim_stat_lbl->setText(QString());
        label_17->setText(QCoreApplication::translate("WgtSim", "Progress bar", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WgtSim", "Set temperature", nullptr));
        label_18->setText(QCoreApplication::translate("WgtSim", "T = ", nullptr));
        set_temp_ln->setInputMask(QString());
        set_temp_ln->setText(QString());
        label_19->setText(QCoreApplication::translate("WgtSim", "[\302\260C]", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WgtSim", "Current data", nullptr));
        label_2->setText(QCoreApplication::translate("WgtSim", "Estimated time: ", nullptr));
        est_time_lbl->setText(QString());
        sim_time_lbl->setText(QString());
        set_curr_lbl->setText(QString());
        label_16->setText(QCoreApplication::translate("WgtSim", " [A]", nullptr));
        label_7->setText(QCoreApplication::translate("WgtSim", "Set current: ", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("WgtSim", "Measured data", nullptr));
        label_4->setText(QCoreApplication::translate("WgtSim", "I = ", nullptr));
        current_lbl->setText(QString());
        label_6->setText(QCoreApplication::translate("WgtSim", " [A]", nullptr));
        label_3->setText(QString());
        label_5->setText(QCoreApplication::translate("WgtSim", "U_L = ", nullptr));
        vol_left_lbl->setText(QString());
        label_8->setText(QCoreApplication::translate("WgtSim", " [V]", nullptr));
        label_14->setText(QCoreApplication::translate("WgtSim", "T_L = ", nullptr));
        temp_left_lbl->setText(QString());
        label_15->setText(QCoreApplication::translate("WgtSim", " [\302\260C]", nullptr));
        label_9->setText(QCoreApplication::translate("WgtSim", "U_R = ", nullptr));
        vol_right_lbl->setText(QString());
        label_11->setText(QCoreApplication::translate("WgtSim", " [V]", nullptr));
        label_10->setText(QCoreApplication::translate("WgtSim", "T_R = ", nullptr));
        temp_right_lbl->setText(QString());
        label_12->setText(QCoreApplication::translate("WgtSim", " [\302\260C]", nullptr));
        label->setText(QCoreApplication::translate("WgtSim", "Simulation time: ", nullptr));
        curr_chart_box->setTitle(QCoreApplication::translate("WgtSim", "Current chart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtSim: public Ui_WgtSim {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTSIM_H

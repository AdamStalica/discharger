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
    QGridLayout *volt_chart_lay_2;
    QGroupBox *curr_chart_box;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *curr_chart_lay;
    QGroupBox *vol_chart_box;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *volt_chart_lay;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_5;
    QPushButton *back_btn;
    QSpacerItem *horizontalSpacer_10;
    QLabel *sim_name;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *start_stop_btn;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_13;
    QLabel *sim_stat_lbl;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_17;
    QProgressBar *sim_progress_bar;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_18;
    QLineEdit *set_temp_ln;
    QLabel *label_19;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QLabel *finished_name_lbl;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_20;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_16;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QLabel *est_time_lbl;
    QLabel *sim_time_lbl;
    QLabel *set_curr_lbl;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QLabel *finished_at_lbl;
    QLabel *started_at_lbl;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_4;
    QLabel *current_lbl;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *vol_left_lbl;
    QLabel *id_left_batt;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *temp_left_lbl;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_3;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *vol_right_lbl;
    QLabel *id_right_batt;
    QLabel *label_10;
    QLabel *temp_right_lbl;
    QLabel *label_12;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *WgtSim)
    {
        if (WgtSim->objectName().isEmpty())
            WgtSim->setObjectName(QString::fromUtf8("WgtSim"));
        WgtSim->resize(1096, 1018);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtSim->sizePolicy().hasHeightForWidth());
        WgtSim->setSizePolicy(sizePolicy);
        WgtSim->setMinimumSize(QSize(450, 700));
        volt_chart_lay_2 = new QGridLayout(WgtSim);
        volt_chart_lay_2->setSpacing(5);
        volt_chart_lay_2->setContentsMargins(11, 11, 11, 11);
        volt_chart_lay_2->setObjectName(QString::fromUtf8("volt_chart_lay_2"));
        volt_chart_lay_2->setContentsMargins(5, 5, 5, 5);
        curr_chart_box = new QGroupBox(WgtSim);
        curr_chart_box->setObjectName(QString::fromUtf8("curr_chart_box"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(curr_chart_box->sizePolicy().hasHeightForWidth());
        curr_chart_box->setSizePolicy(sizePolicy1);
        curr_chart_box->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_6 = new QVBoxLayout(curr_chart_box);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        curr_chart_lay = new QVBoxLayout();
        curr_chart_lay->setSpacing(0);
        curr_chart_lay->setObjectName(QString::fromUtf8("curr_chart_lay"));

        verticalLayout_6->addLayout(curr_chart_lay);


        volt_chart_lay_2->addWidget(curr_chart_box, 0, 1, 1, 1);

        vol_chart_box = new QGroupBox(WgtSim);
        vol_chart_box->setObjectName(QString::fromUtf8("vol_chart_box"));
        sizePolicy1.setHeightForWidth(vol_chart_box->sizePolicy().hasHeightForWidth());
        vol_chart_box->setSizePolicy(sizePolicy1);
        vol_chart_box->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(vol_chart_box);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        volt_chart_lay = new QVBoxLayout();
        volt_chart_lay->setSpacing(6);
        volt_chart_lay->setObjectName(QString::fromUtf8("volt_chart_lay"));

        verticalLayout_2->addLayout(volt_chart_lay);


        volt_chart_lay_2->addWidget(vol_chart_box, 1, 1, 1, 1);

        groupBox_5 = new QGroupBox(WgtSim);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy2);
        groupBox_5->setMinimumSize(QSize(290, 820));
        groupBox_5->setMaximumSize(QSize(290, 820));
        verticalLayout_5 = new QVBoxLayout(groupBox_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        back_btn = new QPushButton(groupBox_5);
        back_btn->setObjectName(QString::fromUtf8("back_btn"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(back_btn->sizePolicy().hasHeightForWidth());
        back_btn->setSizePolicy(sizePolicy3);
        back_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_5->addWidget(back_btn);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_5->addItem(horizontalSpacer_10);

        sim_name = new QLabel(groupBox_5);
        sim_name->setObjectName(QString::fromUtf8("sim_name"));
        sim_name->setStyleSheet(QString::fromUtf8("font-size: 18px;"));

        verticalLayout_5->addWidget(sim_name);

        horizontalSpacer_9 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_5->addItem(horizontalSpacer_9);

        groupBox_2 = new QGroupBox(groupBox_5);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(270, 0));
        groupBox_2->setMaximumSize(QSize(270, 16777215));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        start_stop_btn = new QPushButton(groupBox_2);
        start_stop_btn->setObjectName(QString::fromUtf8("start_stop_btn"));
        sizePolicy3.setHeightForWidth(start_stop_btn->sizePolicy().hasHeightForWidth());
        start_stop_btn->setSizePolicy(sizePolicy3);
        start_stop_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_4->addWidget(start_stop_btn, 0, Qt::AlignHCenter);

        horizontalSpacer_8 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(horizontalSpacer_8);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy4);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_13);

        sim_stat_lbl = new QLabel(groupBox_2);
        sim_stat_lbl->setObjectName(QString::fromUtf8("sim_stat_lbl"));
        sizePolicy4.setHeightForWidth(sim_stat_lbl->sizePolicy().hasHeightForWidth());
        sim_stat_lbl->setSizePolicy(sizePolicy4);

        horizontalLayout_8->addWidget(sim_stat_lbl);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalSpacer_7 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(horizontalSpacer_7);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        verticalLayout_4->addWidget(label_17);

        sim_progress_bar = new QProgressBar(groupBox_2);
        sim_progress_bar->setObjectName(QString::fromUtf8("sim_progress_bar"));
        sim_progress_bar->setValue(0);

        verticalLayout_4->addWidget(sim_progress_bar);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy5);
        groupBox_3->setMinimumSize(QSize(270, 51));
        groupBox_3->setMaximumSize(QSize(270, 51));
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
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy6);
        groupBox->setMinimumSize(QSize(270, 0));
        groupBox->setMaximumSize(QSize(270, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        finished_name_lbl = new QLabel(groupBox);
        finished_name_lbl->setObjectName(QString::fromUtf8("finished_name_lbl"));
        finished_name_lbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(finished_name_lbl, 3, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy4);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label, 5, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 8, 0, 1, 3);

        horizontalSpacer_3 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 10, 0, 1, 3);

        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_20, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 4, 0, 1, 3);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy7);

        gridLayout_4->addWidget(label_16, 9, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy4.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy4);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_2, 7, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 6, 0, 1, 3);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy8);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_7, 9, 0, 1, 1);

        est_time_lbl = new QLabel(groupBox);
        est_time_lbl->setObjectName(QString::fromUtf8("est_time_lbl"));
        sizePolicy4.setHeightForWidth(est_time_lbl->sizePolicy().hasHeightForWidth());
        est_time_lbl->setSizePolicy(sizePolicy4);

        gridLayout_4->addWidget(est_time_lbl, 7, 1, 1, 2);

        sim_time_lbl = new QLabel(groupBox);
        sim_time_lbl->setObjectName(QString::fromUtf8("sim_time_lbl"));
        sizePolicy4.setHeightForWidth(sim_time_lbl->sizePolicy().hasHeightForWidth());
        sim_time_lbl->setSizePolicy(sizePolicy4);

        gridLayout_4->addWidget(sim_time_lbl, 5, 1, 1, 2);

        set_curr_lbl = new QLabel(groupBox);
        set_curr_lbl->setObjectName(QString::fromUtf8("set_curr_lbl"));
        sizePolicy4.setHeightForWidth(set_curr_lbl->sizePolicy().hasHeightForWidth());
        set_curr_lbl->setSizePolicy(sizePolicy4);

        gridLayout_4->addWidget(set_curr_lbl, 9, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 2, 0, 1, 3);

        horizontalSpacer_6 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_6, 0, 0, 1, 3);

        finished_at_lbl = new QLabel(groupBox);
        finished_at_lbl->setObjectName(QString::fromUtf8("finished_at_lbl"));
        sizePolicy4.setHeightForWidth(finished_at_lbl->sizePolicy().hasHeightForWidth());
        finished_at_lbl->setSizePolicy(sizePolicy4);

        gridLayout_4->addWidget(finished_at_lbl, 3, 1, 1, 2);

        started_at_lbl = new QLabel(groupBox);
        started_at_lbl->setObjectName(QString::fromUtf8("started_at_lbl"));
        sizePolicy4.setHeightForWidth(started_at_lbl->sizePolicy().hasHeightForWidth());
        started_at_lbl->setSizePolicy(sizePolicy4);

        gridLayout_4->addWidget(started_at_lbl, 1, 1, 1, 2);


        gridLayout->addLayout(gridLayout_4, 0, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox);

        groupBox_4 = new QGroupBox(groupBox_5);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy9(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy9);
        groupBox_4->setMinimumSize(QSize(270, 230));
        groupBox_4->setMaximumSize(QSize(270, 300));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalSpacer_3 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(verticalSpacer_3);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy4.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(label_4, 0, Qt::AlignRight);

        current_lbl = new QLabel(groupBox_4);
        current_lbl->setObjectName(QString::fromUtf8("current_lbl"));
        sizePolicy4.setHeightForWidth(current_lbl->sizePolicy().hasHeightForWidth());
        current_lbl->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(current_lbl, 0, Qt::AlignHCenter);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy4.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(label_6, 0, Qt::AlignLeft);

        verticalSpacer_2 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(verticalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy10.setHorizontalStretch(50);
        sizePolicy10.setVerticalStretch(15);
        sizePolicy10.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy10);
        label_3->setMinimumSize(QSize(250, 120));
        label_3->setMaximumSize(QSize(250, 120));
        label_3->setSizeIncrement(QSize(50, 100));
        label_3->setBaseSize(QSize(50, 100));
        label_3->setPixmap(QPixmap(QString::fromUtf8("media/schem_transparent.png")));
        label_3->setScaledContents(true);

        verticalLayout->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalSpacer_4 = new QSpacerItem(10, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_4->addItem(verticalSpacer_4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy4.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(label_8, 1, 2, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy4.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        vol_left_lbl = new QLabel(groupBox_4);
        vol_left_lbl->setObjectName(QString::fromUtf8("vol_left_lbl"));
        sizePolicy4.setHeightForWidth(vol_left_lbl->sizePolicy().hasHeightForWidth());
        vol_left_lbl->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(vol_left_lbl, 1, 1, 1, 1);

        id_left_batt = new QLabel(groupBox_4);
        id_left_batt->setObjectName(QString::fromUtf8("id_left_batt"));
        id_left_batt->setStyleSheet(QString::fromUtf8("font-size: 16px;"));
        id_left_batt->setTextFormat(Qt::RichText);
        id_left_batt->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(id_left_batt, 0, 0, 1, 3);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy4.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(label_14, 2, 0, 1, 1);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy4.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(label_15, 2, 2, 1, 1);

        temp_left_lbl = new QLabel(groupBox_4);
        temp_left_lbl->setObjectName(QString::fromUtf8("temp_left_lbl"));
        sizePolicy4.setHeightForWidth(temp_left_lbl->sizePolicy().hasHeightForWidth());
        temp_left_lbl->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(temp_left_lbl, 2, 1, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_2);

        verticalSpacer = new QSpacerItem(10, 30, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(verticalSpacer);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy4.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_9, 1, 0, 1, 1);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy4.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_11, 1, 2, 1, 1);

        vol_right_lbl = new QLabel(groupBox_4);
        vol_right_lbl->setObjectName(QString::fromUtf8("vol_right_lbl"));
        sizePolicy4.setHeightForWidth(vol_right_lbl->sizePolicy().hasHeightForWidth());
        vol_right_lbl->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(vol_right_lbl, 1, 1, 1, 1);

        id_right_batt = new QLabel(groupBox_4);
        id_right_batt->setObjectName(QString::fromUtf8("id_right_batt"));
        id_right_batt->setStyleSheet(QString::fromUtf8("font-size: 16px;"));
        id_right_batt->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(id_right_batt, 0, 0, 1, 3);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy4.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_10, 2, 0, 1, 1);

        temp_right_lbl = new QLabel(groupBox_4);
        temp_right_lbl->setObjectName(QString::fromUtf8("temp_right_lbl"));
        sizePolicy4.setHeightForWidth(temp_right_lbl->sizePolicy().hasHeightForWidth());
        temp_right_lbl->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(temp_right_lbl, 2, 1, 1, 1);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy4.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_12, 2, 2, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_3);

        verticalSpacer_5 = new QSpacerItem(10, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_4->addItem(verticalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_5->addWidget(groupBox_4);


        volt_chart_lay_2->addWidget(groupBox_5, 0, 0, 2, 1, Qt::AlignTop);


        retranslateUi(WgtSim);

        QMetaObject::connectSlotsByName(WgtSim);
    } // setupUi

    void retranslateUi(QWidget *WgtSim)
    {
        WgtSim->setWindowTitle(QCoreApplication::translate("WgtSim", "WgtSim", nullptr));
        curr_chart_box->setTitle(QCoreApplication::translate("WgtSim", "Current chart", nullptr));
        vol_chart_box->setTitle(QCoreApplication::translate("WgtSim", "Voltage chart", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("WgtSim", "Data and Control", nullptr));
        back_btn->setText(QCoreApplication::translate("WgtSim", "Go back", nullptr));
        sim_name->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("WgtSim", "Control", nullptr));
        start_stop_btn->setText(QCoreApplication::translate("WgtSim", "Start", nullptr));
        label_13->setText(QCoreApplication::translate("WgtSim", "Simulation status: ", nullptr));
        sim_stat_lbl->setText(QCoreApplication::translate("WgtSim", "Not started yet", nullptr));
        label_17->setText(QCoreApplication::translate("WgtSim", "Progress bar", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WgtSim", "Set temperature", nullptr));
        label_18->setText(QCoreApplication::translate("WgtSim", "T = ", nullptr));
        set_temp_ln->setInputMask(QString());
        set_temp_ln->setText(QCoreApplication::translate("WgtSim", "20.0", nullptr));
        label_19->setText(QCoreApplication::translate("WgtSim", "[\302\260C]", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WgtSim", "Current data", nullptr));
        finished_name_lbl->setText(QCoreApplication::translate("WgtSim", "Estimated end: ", nullptr));
        label->setText(QCoreApplication::translate("WgtSim", "Simulation time: ", nullptr));
        label_20->setText(QCoreApplication::translate("WgtSim", "Started at: ", nullptr));
        label_16->setText(QCoreApplication::translate("WgtSim", " [A]", nullptr));
        label_2->setText(QCoreApplication::translate("WgtSim", "Estimated time: ", nullptr));
        label_7->setText(QCoreApplication::translate("WgtSim", "Set current: ", nullptr));
        est_time_lbl->setText(QString());
        sim_time_lbl->setText(QString());
        set_curr_lbl->setText(QString());
        finished_at_lbl->setText(QString());
        started_at_lbl->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("WgtSim", "Measured data", nullptr));
        label_4->setText(QCoreApplication::translate("WgtSim", "I = ", nullptr));
        current_lbl->setText(QString());
        label_6->setText(QCoreApplication::translate("WgtSim", " [A]", nullptr));
        label_3->setText(QString());
        label_8->setText(QCoreApplication::translate("WgtSim", " [V]", nullptr));
        label_5->setText(QCoreApplication::translate("WgtSim", "U_L = ", nullptr));
        vol_left_lbl->setText(QString());
        id_left_batt->setText(QString());
        label_14->setText(QCoreApplication::translate("WgtSim", "T_L = ", nullptr));
        label_15->setText(QCoreApplication::translate("WgtSim", " [\302\260C]", nullptr));
        temp_left_lbl->setText(QString());
        label_9->setText(QCoreApplication::translate("WgtSim", "U_R = ", nullptr));
        label_11->setText(QCoreApplication::translate("WgtSim", " [V]", nullptr));
        vol_right_lbl->setText(QString());
        id_right_batt->setText(QString());
        label_10->setText(QCoreApplication::translate("WgtSim", "T_R = ", nullptr));
        temp_right_lbl->setText(QString());
        label_12->setText(QCoreApplication::translate("WgtSim", " [\302\260C]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtSim: public Ui_WgtSim {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTSIM_H

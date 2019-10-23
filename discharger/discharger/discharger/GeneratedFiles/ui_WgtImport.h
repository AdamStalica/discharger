/********************************************************************************
** Form generated from reading UI file 'WgtImport.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
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
    QPushButton *go_back_btn;
    QGroupBox *sp_box;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *sp_lay;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *sp_list;
    QPushButton *sp_btn;
    QGroupBox *race_box;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *race_lay;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *race_list;
    QPushButton *race_btn;
    QGroupBox *lg_box;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *lg_fp_ln;
    QPushButton *lg_fp_btn;
    QComboBox *lg_batt_r_list;
    QLabel *label_4;
    QComboBox *lg_types_list;
    QLabel *label_3;
    QComboBox *lg_batt_l_list;
    QComboBox *lg_car_list;
    QLabel *label_7;
    QGroupBox *col_mask_box;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_4;
    QLabel *label_30;
    QComboBox *col_mask_list;
    QWidget *col_save_box;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_31;
    QLineEdit *col_new_msk_ln;
    QPushButton *col_new_msk_btn;
    QGroupBox *col_box;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QComboBox *motor_curr_race_avg;
    QComboBox *motor_curr_lap_avg;
    QComboBox *temp_2;
    QLabel *label_18;
    QComboBox *temp_1;
    QLabel *label_9;
    QComboBox *curr_race_time;
    QLabel *label_17;
    QComboBox *temp_3;
    QComboBox *curr_lap_time;
    QComboBox *tachometer_rpm;
    QLabel *label_25;
    QComboBox *gps_longitude;
    QLabel *label_28;
    QComboBox *main_curr_lap_avg;
    QLabel *label_19;
    QLabel *label_12;
    QLabel *label_29;
    QComboBox *batt_left_volt;
    QComboBox *motor_curr;
    QLabel *label_21;
    QLabel *label_27;
    QLabel *label_8;
    QComboBox *laps_num;
    QComboBox *main_curr;
    QComboBox *batt_right_volt;
    QComboBox *id_control_type;
    QComboBox *tachometer_speed;
    QLabel *label_16;
    QLabel *label_13;
    QComboBox *curr_timestamp;
    QLabel *label_15;
    QLabel *label_26;
    QLabel *label_22;
    QLabel *label_14;
    QLabel *label_11;
    QComboBox *gps_latitude;
    QComboBox *main_curr_race_avg;
    QLabel *label_23;
    QComboBox *measurment_id;
    QLabel *label_20;
    QLabel *label_24;
    QComboBox *gps_speed;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *cnl_btn;
    QPushButton *import_btn;

    void setupUi(QWidget *WgtImport)
    {
        if (WgtImport->objectName().isEmpty())
            WgtImport->setObjectName(QString::fromUtf8("WgtImport"));
        WgtImport->resize(510, 1441);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
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
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(492, 0));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        go_back_btn = new QPushButton(groupBox_3);
        go_back_btn->setObjectName(QString::fromUtf8("go_back_btn"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(go_back_btn->sizePolicy().hasHeightForWidth());
        go_back_btn->setSizePolicy(sizePolicy1);
        go_back_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_5->addWidget(go_back_btn);

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
        sizePolicy1.setHeightForWidth(sp_list->sizePolicy().hasHeightForWidth());
        sp_list->setSizePolicy(sizePolicy1);
        sp_list->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(sp_list);


        sp_lay->addLayout(horizontalLayout);

        sp_btn = new QPushButton(sp_box);
        sp_btn->setObjectName(QString::fromUtf8("sp_btn"));
        sizePolicy1.setHeightForWidth(sp_btn->sizePolicy().hasHeightForWidth());
        sp_btn->setSizePolicy(sizePolicy1);
        sp_btn->setMinimumSize(QSize(150, 0));
        sp_btn->setMaximumSize(QSize(150, 16777215));
        sp_btn->setLayoutDirection(Qt::LeftToRight);

        sp_lay->addWidget(sp_btn, 0, Qt::AlignRight);


        verticalLayout->addLayout(sp_lay);


        verticalLayout_5->addWidget(sp_box);

        race_box = new QGroupBox(groupBox_3);
        race_box->setObjectName(QString::fromUtf8("race_box"));
        race_box->setEnabled(false);
        sizePolicy2.setHeightForWidth(race_box->sizePolicy().hasHeightForWidth());
        race_box->setSizePolicy(sizePolicy2);
        race_box->setMinimumSize(QSize(460, 0));
        verticalLayout_3 = new QVBoxLayout(race_box);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        race_lay = new QVBoxLayout();
        race_lay->setSpacing(6);
        race_lay->setObjectName(QString::fromUtf8("race_lay"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(race_box);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        race_list = new QComboBox(race_box);
        race_list->setObjectName(QString::fromUtf8("race_list"));
        sizePolicy1.setHeightForWidth(race_list->sizePolicy().hasHeightForWidth());
        race_list->setSizePolicy(sizePolicy1);
        race_list->setMinimumSize(QSize(300, 0));

        horizontalLayout_2->addWidget(race_list);


        race_lay->addLayout(horizontalLayout_2);

        race_btn = new QPushButton(race_box);
        race_btn->setObjectName(QString::fromUtf8("race_btn"));
        sizePolicy1.setHeightForWidth(race_btn->sizePolicy().hasHeightForWidth());
        race_btn->setSizePolicy(sizePolicy1);
        race_btn->setMinimumSize(QSize(150, 0));

        race_lay->addWidget(race_btn, 0, Qt::AlignRight);


        verticalLayout_3->addLayout(race_lay);


        verticalLayout_5->addWidget(race_box);

        lg_box = new QGroupBox(groupBox_3);
        lg_box->setObjectName(QString::fromUtf8("lg_box"));
        lg_box->setEnabled(false);
        sizePolicy2.setHeightForWidth(lg_box->sizePolicy().hasHeightForWidth());
        lg_box->setSizePolicy(sizePolicy2);
        verticalLayout_6 = new QVBoxLayout(lg_box);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(lg_box);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(lg_box);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);
        label_6->setMinimumSize(QSize(120, 60));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_6);

        lg_fp_ln = new QLineEdit(lg_box);
        lg_fp_ln->setObjectName(QString::fromUtf8("lg_fp_ln"));
        sizePolicy1.setHeightForWidth(lg_fp_ln->sizePolicy().hasHeightForWidth());
        lg_fp_ln->setSizePolicy(sizePolicy1);
        lg_fp_ln->setMinimumSize(QSize(219, 0));

        horizontalLayout_3->addWidget(lg_fp_ln);

        lg_fp_btn = new QPushButton(lg_box);
        lg_fp_btn->setObjectName(QString::fromUtf8("lg_fp_btn"));
        sizePolicy1.setHeightForWidth(lg_fp_btn->sizePolicy().hasHeightForWidth());
        lg_fp_btn->setSizePolicy(sizePolicy1);
        lg_fp_btn->setMinimumSize(QSize(70, 0));

        horizontalLayout_3->addWidget(lg_fp_btn);


        gridLayout->addLayout(horizontalLayout_3, 5, 0, 1, 2);

        lg_batt_r_list = new QComboBox(lg_box);
        lg_batt_r_list->setObjectName(QString::fromUtf8("lg_batt_r_list"));

        gridLayout->addWidget(lg_batt_r_list, 3, 1, 1, 1);

        label_4 = new QLabel(lg_box);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lg_types_list = new QComboBox(lg_box);
        lg_types_list->setObjectName(QString::fromUtf8("lg_types_list"));
        sizePolicy1.setHeightForWidth(lg_types_list->sizePolicy().hasHeightForWidth());
        lg_types_list->setSizePolicy(sizePolicy1);
        lg_types_list->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(lg_types_list, 0, 1, 1, 1);

        label_3 = new QLabel(lg_box);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lg_batt_l_list = new QComboBox(lg_box);
        lg_batt_l_list->setObjectName(QString::fromUtf8("lg_batt_l_list"));

        gridLayout->addWidget(lg_batt_l_list, 2, 1, 1, 1);

        lg_car_list = new QComboBox(lg_box);
        lg_car_list->setObjectName(QString::fromUtf8("lg_car_list"));

        gridLayout->addWidget(lg_car_list, 1, 1, 1, 1);

        label_7 = new QLabel(lg_box);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 1, 0, 1, 1);


        verticalLayout_6->addLayout(gridLayout);


        verticalLayout_5->addWidget(lg_box);

        col_mask_box = new QGroupBox(groupBox_3);
        col_mask_box->setObjectName(QString::fromUtf8("col_mask_box"));
        col_mask_box->setEnabled(false);
        verticalLayout_7 = new QVBoxLayout(col_mask_box);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_30 = new QLabel(col_mask_box);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy4);
        label_30->setMinimumSize(QSize(0, 30));
        label_30->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_30, 0, 0, 1, 1);

        col_mask_list = new QComboBox(col_mask_box);
        col_mask_list->addItem(QString());
        col_mask_list->setObjectName(QString::fromUtf8("col_mask_list"));
        sizePolicy1.setHeightForWidth(col_mask_list->sizePolicy().hasHeightForWidth());
        col_mask_list->setSizePolicy(sizePolicy1);
        col_mask_list->setMinimumSize(QSize(300, 0));

        gridLayout_4->addWidget(col_mask_list, 0, 1, 1, 1);

        col_save_box = new QWidget(col_mask_box);
        col_save_box->setObjectName(QString::fromUtf8("col_save_box"));
        col_save_box->setEnabled(false);
        horizontalLayout_4 = new QHBoxLayout(col_save_box);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 0, -1);
        label_31 = new QLabel(col_save_box);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_31);

        col_new_msk_ln = new QLineEdit(col_save_box);
        col_new_msk_ln->setObjectName(QString::fromUtf8("col_new_msk_ln"));
        sizePolicy1.setHeightForWidth(col_new_msk_ln->sizePolicy().hasHeightForWidth());
        col_new_msk_ln->setSizePolicy(sizePolicy1);
        col_new_msk_ln->setMinimumSize(QSize(219, 0));

        horizontalLayout_4->addWidget(col_new_msk_ln);

        col_new_msk_btn = new QPushButton(col_save_box);
        col_new_msk_btn->setObjectName(QString::fromUtf8("col_new_msk_btn"));
        sizePolicy1.setHeightForWidth(col_new_msk_btn->sizePolicy().hasHeightForWidth());
        col_new_msk_btn->setSizePolicy(sizePolicy1);
        col_new_msk_btn->setMinimumSize(QSize(70, 0));

        horizontalLayout_4->addWidget(col_new_msk_btn);


        gridLayout_4->addWidget(col_save_box, 1, 0, 1, 2);


        verticalLayout_7->addLayout(gridLayout_4);


        verticalLayout_5->addWidget(col_mask_box);

        col_box = new QGroupBox(groupBox_3);
        col_box->setObjectName(QString::fromUtf8("col_box"));
        col_box->setEnabled(false);
        sizePolicy4.setHeightForWidth(col_box->sizePolicy().hasHeightForWidth());
        col_box->setSizePolicy(sizePolicy4);
        verticalLayout_2 = new QVBoxLayout(col_box);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_10 = new QLabel(col_box);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy4.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy4);
        label_10->setMinimumSize(QSize(0, 30));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_10, 2, 0, 1, 1);

        motor_curr_race_avg = new QComboBox(col_box);
        motor_curr_race_avg->setObjectName(QString::fromUtf8("motor_curr_race_avg"));

        gridLayout_2->addWidget(motor_curr_race_avg, 8, 1, 1, 1);

        motor_curr_lap_avg = new QComboBox(col_box);
        motor_curr_lap_avg->setObjectName(QString::fromUtf8("motor_curr_lap_avg"));

        gridLayout_2->addWidget(motor_curr_lap_avg, 7, 1, 1, 1);

        temp_2 = new QComboBox(col_box);
        temp_2->setObjectName(QString::fromUtf8("temp_2"));

        gridLayout_2->addWidget(temp_2, 20, 1, 1, 1);

        label_18 = new QLabel(col_box);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy4.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy4);
        label_18->setMinimumSize(QSize(0, 30));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_18, 10, 0, 1, 1);

        temp_1 = new QComboBox(col_box);
        temp_1->setObjectName(QString::fromUtf8("temp_1"));

        gridLayout_2->addWidget(temp_1, 19, 1, 1, 1);

        label_9 = new QLabel(col_box);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy4.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy4);
        label_9->setMinimumSize(QSize(0, 30));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        curr_race_time = new QComboBox(col_box);
        curr_race_time->setObjectName(QString::fromUtf8("curr_race_time"));

        gridLayout_2->addWidget(curr_race_time, 3, 1, 1, 1);

        label_17 = new QLabel(col_box);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy4.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy4);
        label_17->setMinimumSize(QSize(0, 30));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_17, 9, 0, 1, 1);

        temp_3 = new QComboBox(col_box);
        temp_3->setObjectName(QString::fromUtf8("temp_3"));

        gridLayout_2->addWidget(temp_3, 21, 1, 1, 1);

        curr_lap_time = new QComboBox(col_box);
        curr_lap_time->setObjectName(QString::fromUtf8("curr_lap_time"));

        gridLayout_2->addWidget(curr_lap_time, 4, 1, 1, 1);

        tachometer_rpm = new QComboBox(col_box);
        tachometer_rpm->setObjectName(QString::fromUtf8("tachometer_rpm"));

        gridLayout_2->addWidget(tachometer_rpm, 14, 1, 1, 1);

        label_25 = new QLabel(col_box);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy4.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy4);
        label_25->setMinimumSize(QSize(0, 30));
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_25, 17, 0, 1, 1);

        gps_longitude = new QComboBox(col_box);
        gps_longitude->setObjectName(QString::fromUtf8("gps_longitude"));

        gridLayout_2->addWidget(gps_longitude, 18, 1, 1, 1);

        label_28 = new QLabel(col_box);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        sizePolicy4.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy4);
        label_28->setMinimumSize(QSize(0, 30));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_28, 20, 0, 1, 1);

        main_curr_lap_avg = new QComboBox(col_box);
        main_curr_lap_avg->setObjectName(QString::fromUtf8("main_curr_lap_avg"));

        gridLayout_2->addWidget(main_curr_lap_avg, 10, 1, 1, 1);

        label_19 = new QLabel(col_box);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy4.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy4);
        label_19->setMinimumSize(QSize(0, 30));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_19, 11, 0, 1, 1);

        label_12 = new QLabel(col_box);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy4.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy4);
        label_12->setMinimumSize(QSize(0, 30));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_12, 4, 0, 1, 1);

        label_29 = new QLabel(col_box);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        sizePolicy4.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy4);
        label_29->setMinimumSize(QSize(0, 30));
        label_29->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_29, 21, 0, 1, 1);

        batt_left_volt = new QComboBox(col_box);
        batt_left_volt->setObjectName(QString::fromUtf8("batt_left_volt"));

        gridLayout_2->addWidget(batt_left_volt, 12, 1, 1, 1);

        motor_curr = new QComboBox(col_box);
        motor_curr->setObjectName(QString::fromUtf8("motor_curr"));

        gridLayout_2->addWidget(motor_curr, 6, 1, 1, 1);

        label_21 = new QLabel(col_box);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy4.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy4);
        label_21->setMinimumSize(QSize(0, 30));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_21, 13, 0, 1, 1);

        label_27 = new QLabel(col_box);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        sizePolicy4.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy4);
        label_27->setMinimumSize(QSize(0, 30));
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_27, 19, 0, 1, 1);

        label_8 = new QLabel(col_box);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy4.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy4);
        label_8->setMinimumSize(QSize(0, 30));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        laps_num = new QComboBox(col_box);
        laps_num->setObjectName(QString::fromUtf8("laps_num"));

        gridLayout_2->addWidget(laps_num, 5, 1, 1, 1);

        main_curr = new QComboBox(col_box);
        main_curr->setObjectName(QString::fromUtf8("main_curr"));

        gridLayout_2->addWidget(main_curr, 9, 1, 1, 1);

        batt_right_volt = new QComboBox(col_box);
        batt_right_volt->setObjectName(QString::fromUtf8("batt_right_volt"));

        gridLayout_2->addWidget(batt_right_volt, 13, 1, 1, 1);

        id_control_type = new QComboBox(col_box);
        id_control_type->setObjectName(QString::fromUtf8("id_control_type"));
        sizePolicy4.setHeightForWidth(id_control_type->sizePolicy().hasHeightForWidth());
        id_control_type->setSizePolicy(sizePolicy4);
        id_control_type->setMinimumSize(QSize(300, 0));

        gridLayout_2->addWidget(id_control_type, 0, 1, 1, 1);

        tachometer_speed = new QComboBox(col_box);
        tachometer_speed->setObjectName(QString::fromUtf8("tachometer_speed"));

        gridLayout_2->addWidget(tachometer_speed, 15, 1, 1, 1);

        label_16 = new QLabel(col_box);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy4.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy4);
        label_16->setMinimumSize(QSize(0, 30));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_16, 8, 0, 1, 1);

        label_13 = new QLabel(col_box);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy4.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy4);
        label_13->setMinimumSize(QSize(0, 30));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_13, 5, 0, 1, 1);

        curr_timestamp = new QComboBox(col_box);
        curr_timestamp->setObjectName(QString::fromUtf8("curr_timestamp"));

        gridLayout_2->addWidget(curr_timestamp, 2, 1, 1, 1);

        label_15 = new QLabel(col_box);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy4.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy4);
        label_15->setMinimumSize(QSize(0, 30));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_15, 7, 0, 1, 1);

        label_26 = new QLabel(col_box);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy4.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy4);
        label_26->setMinimumSize(QSize(0, 30));
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_26, 18, 0, 1, 1);

        label_22 = new QLabel(col_box);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy4.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy4);
        label_22->setMinimumSize(QSize(0, 30));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_22, 14, 0, 1, 1);

        label_14 = new QLabel(col_box);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy4.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy4);
        label_14->setMinimumSize(QSize(0, 30));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_14, 6, 0, 1, 1);

        label_11 = new QLabel(col_box);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy4.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy4);
        label_11->setMinimumSize(QSize(0, 30));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_11, 3, 0, 1, 1);

        gps_latitude = new QComboBox(col_box);
        gps_latitude->setObjectName(QString::fromUtf8("gps_latitude"));

        gridLayout_2->addWidget(gps_latitude, 17, 1, 1, 1);

        main_curr_race_avg = new QComboBox(col_box);
        main_curr_race_avg->setObjectName(QString::fromUtf8("main_curr_race_avg"));

        gridLayout_2->addWidget(main_curr_race_avg, 11, 1, 1, 1);

        label_23 = new QLabel(col_box);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy4.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy4);
        label_23->setMinimumSize(QSize(0, 30));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_23, 15, 0, 1, 1);

        measurment_id = new QComboBox(col_box);
        measurment_id->setObjectName(QString::fromUtf8("measurment_id"));

        gridLayout_2->addWidget(measurment_id, 1, 1, 1, 1);

        label_20 = new QLabel(col_box);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy4.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy4);
        label_20->setMinimumSize(QSize(0, 30));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_20, 12, 0, 1, 1);

        label_24 = new QLabel(col_box);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        sizePolicy4.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy4);
        label_24->setMinimumSize(QSize(0, 30));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_24, 16, 0, 1, 1);

        gps_speed = new QComboBox(col_box);
        gps_speed->setObjectName(QString::fromUtf8("gps_speed"));

        gridLayout_2->addWidget(gps_speed, 16, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout_5->addWidget(col_box);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        cnl_btn = new QPushButton(groupBox_3);
        cnl_btn->setObjectName(QString::fromUtf8("cnl_btn"));
        sizePolicy1.setHeightForWidth(cnl_btn->sizePolicy().hasHeightForWidth());
        cnl_btn->setSizePolicy(sizePolicy1);
        cnl_btn->setMinimumSize(QSize(100, 0));

        horizontalLayout_5->addWidget(cnl_btn, 0, Qt::AlignLeft);

        import_btn = new QPushButton(groupBox_3);
        import_btn->setObjectName(QString::fromUtf8("import_btn"));
        import_btn->setEnabled(false);
        sizePolicy1.setHeightForWidth(import_btn->sizePolicy().hasHeightForWidth());
        import_btn->setSizePolicy(sizePolicy1);
        import_btn->setMinimumSize(QSize(100, 0));

        horizontalLayout_5->addWidget(import_btn, 0, Qt::AlignRight);


        verticalLayout_5->addLayout(horizontalLayout_5);


        verticalLayout_4->addWidget(groupBox_3, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        retranslateUi(WgtImport);

        QMetaObject::connectSlotsByName(WgtImport);
    } // setupUi

    void retranslateUi(QWidget *WgtImport)
    {
        WgtImport->setWindowTitle(QCoreApplication::translate("WgtImport", "WgtImport", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WgtImport", "Import logs into the Data Base", nullptr));
        go_back_btn->setText(QCoreApplication::translate("WgtImport", "Go back", nullptr));
        sp_box->setTitle(QCoreApplication::translate("WgtImport", "Speedway", nullptr));
        label->setText(QCoreApplication::translate("WgtImport", "Select speedway: ", nullptr));
        sp_btn->setText(QCoreApplication::translate("WgtImport", "New speedway", nullptr));
        race_box->setTitle(QCoreApplication::translate("WgtImport", "Race", nullptr));
        label_2->setText(QCoreApplication::translate("WgtImport", "Select race: ", nullptr));
        race_btn->setText(QCoreApplication::translate("WgtImport", "New race", nullptr));
        lg_box->setTitle(QCoreApplication::translate("WgtImport", "Logs", nullptr));
        label_5->setText(QCoreApplication::translate("WgtImport", "Right battery: ", nullptr));
        label_6->setText(QCoreApplication::translate("WgtImport", "Choose log file: ", nullptr));
        lg_fp_btn->setText(QCoreApplication::translate("WgtImport", "Open", nullptr));
        label_4->setText(QCoreApplication::translate("WgtImport", "Left battery: ", nullptr));
        label_3->setText(QCoreApplication::translate("WgtImport", "Log type: ", nullptr));
        label_7->setText(QCoreApplication::translate("WgtImport", "Car: ", nullptr));
        col_mask_box->setTitle(QCoreApplication::translate("WgtImport", "Columns mask", nullptr));
        label_30->setText(QCoreApplication::translate("WgtImport", "Select mask: ", nullptr));
        col_mask_list->setItemText(0, QCoreApplication::translate("WgtImport", "New mask", nullptr));

        label_31->setText(QCoreApplication::translate("WgtImport", "New mask name: ", nullptr));
        col_new_msk_btn->setText(QCoreApplication::translate("WgtImport", "Save", nullptr));
        col_box->setTitle(QCoreApplication::translate("WgtImport", "Select columns", nullptr));
        label_10->setText(QCoreApplication::translate("WgtImport", "Current timestamp: ", nullptr));
        label_18->setText(QCoreApplication::translate("WgtImport", "Main current, lap average: ", nullptr));
        label_9->setText(QCoreApplication::translate("WgtImport", "Measurment id: ", nullptr));
        label_17->setText(QCoreApplication::translate("WgtImport", "Main current: ", nullptr));
        label_25->setText(QCoreApplication::translate("WgtImport", "GPS latitude: ", nullptr));
        label_28->setText(QCoreApplication::translate("WgtImport", "Temperature 2: ", nullptr));
        label_19->setText(QCoreApplication::translate("WgtImport", "Main current, race average: ", nullptr));
        label_12->setText(QCoreApplication::translate("WgtImport", "Current lap time: ", nullptr));
        label_29->setText(QCoreApplication::translate("WgtImport", "Temperature 3: ", nullptr));
        label_21->setText(QCoreApplication::translate("WgtImport", "Right battery voltage: ", nullptr));
        label_27->setText(QCoreApplication::translate("WgtImport", "Temperature 1: ", nullptr));
        label_8->setText(QCoreApplication::translate("WgtImport", "Control type: ", nullptr));
        label_16->setText(QCoreApplication::translate("WgtImport", "Motor current, race average: ", nullptr));
        label_13->setText(QCoreApplication::translate("WgtImport", "Count of laps: ", nullptr));
        label_15->setText(QCoreApplication::translate("WgtImport", "Motor current, lap average: ", nullptr));
        label_26->setText(QCoreApplication::translate("WgtImport", "GPS longitude: ", nullptr));
        label_22->setText(QCoreApplication::translate("WgtImport", "Tachometer RPM: ", nullptr));
        label_14->setText(QCoreApplication::translate("WgtImport", "Motor current: ", nullptr));
        label_11->setText(QCoreApplication::translate("WgtImport", "Current race time: ", nullptr));
        label_23->setText(QCoreApplication::translate("WgtImport", "Tachometer speed: ", nullptr));
        label_20->setText(QCoreApplication::translate("WgtImport", "Left battery voltage: ", nullptr));
        label_24->setText(QCoreApplication::translate("WgtImport", "GSP speed: ", nullptr));
        cnl_btn->setText(QCoreApplication::translate("WgtImport", "Cancel", nullptr));
        import_btn->setText(QCoreApplication::translate("WgtImport", "Import", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtImport: public Ui_WgtImport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTIMPORT_H

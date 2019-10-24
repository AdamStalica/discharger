/********************************************************************************
** Form generated from reading UI file 'WgtSimConfig.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTSIMCONFIG_H
#define UI_WGTSIMCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtSimConfig
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer_4;
    QPushButton *go_back_btn;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *dev_box;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *ports_list;
    QPushButton *refresh_btn;
    QPushButton *open_com_btn;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *expand_btn;
    QTreeView *races_tree;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QComboBox *id_batt_left;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_2;
    QComboBox *id_batt_right;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *sim_name;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_6;
    QPushButton *prep_sim_btn;

    void setupUi(QWidget *WgtSimConfig)
    {
        if (WgtSimConfig->objectName().isEmpty())
            WgtSimConfig->setObjectName(QString::fromUtf8("WgtSimConfig"));
        WgtSimConfig->resize(512, 857);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtSimConfig->sizePolicy().hasHeightForWidth());
        WgtSimConfig->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(WgtSimConfig);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox_5 = new QGroupBox(WgtSimConfig);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        verticalLayout_5 = new QVBoxLayout(groupBox_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setMinimumSize(QSize(492, 0));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(1, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalSpacer_4 = new QSpacerItem(9, 9, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(verticalSpacer_4);

        go_back_btn = new QPushButton(groupBox_3);
        go_back_btn->setObjectName(QString::fromUtf8("go_back_btn"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(go_back_btn->sizePolicy().hasHeightForWidth());
        go_back_btn->setSizePolicy(sizePolicy2);
        go_back_btn->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(go_back_btn, 0, Qt::AlignLeft);

        verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(verticalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalSpacer_6 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(horizontalSpacer_6);

        dev_box = new QGroupBox(groupBox_3);
        dev_box->setObjectName(QString::fromUtf8("dev_box"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dev_box->sizePolicy().hasHeightForWidth());
        dev_box->setSizePolicy(sizePolicy3);
        dev_box->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(dev_box);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(dev_box);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        ports_list = new QComboBox(dev_box);
        ports_list->setObjectName(QString::fromUtf8("ports_list"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(ports_list->sizePolicy().hasHeightForWidth());
        ports_list->setSizePolicy(sizePolicy5);
        ports_list->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(ports_list, 2, 1, 1, 1);

        refresh_btn = new QPushButton(dev_box);
        refresh_btn->setObjectName(QString::fromUtf8("refresh_btn"));
        sizePolicy.setHeightForWidth(refresh_btn->sizePolicy().hasHeightForWidth());
        refresh_btn->setSizePolicy(sizePolicy);
        refresh_btn->setMinimumSize(QSize(100, 23));

        gridLayout->addWidget(refresh_btn, 1, 1, 1, 1, Qt::AlignRight);

        open_com_btn = new QPushButton(dev_box);
        open_com_btn->setObjectName(QString::fromUtf8("open_com_btn"));
        sizePolicy.setHeightForWidth(open_com_btn->sizePolicy().hasHeightForWidth());
        open_com_btn->setSizePolicy(sizePolicy);
        open_com_btn->setMinimumSize(QSize(100, 23));

        gridLayout->addWidget(open_com_btn, 3, 1, 1, 1, Qt::AlignRight);

        horizontalSpacer_3 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 2);


        verticalLayout->addWidget(dev_box);

        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(horizontalSpacer_2);

        expand_btn = new QPushButton(groupBox_2);
        expand_btn->setObjectName(QString::fromUtf8("expand_btn"));
        sizePolicy2.setHeightForWidth(expand_btn->sizePolicy().hasHeightForWidth());
        expand_btn->setSizePolicy(sizePolicy2);
        expand_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_3->addWidget(expand_btn, 0, Qt::AlignRight);

        races_tree = new QTreeView(groupBox_2);
        races_tree->setObjectName(QString::fromUtf8("races_tree"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(races_tree->sizePolicy().hasHeightForWidth());
        races_tree->setSizePolicy(sizePolicy6);
        races_tree->setMinimumSize(QSize(0, 300));
        races_tree->setLineWidth(-1);

        verticalLayout_3->addWidget(races_tree);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 3, 1);

        id_batt_left = new QComboBox(groupBox);
        id_batt_left->setObjectName(QString::fromUtf8("id_batt_left"));
        sizePolicy2.setHeightForWidth(id_batt_left->sizePolicy().hasHeightForWidth());
        id_batt_left->setSizePolicy(sizePolicy2);
        id_batt_left->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(id_batt_left, 3, 1, 1, 1, Qt::AlignHCenter);

        verticalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(verticalSpacer_3, 1, 3, 3, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 1, 1, 1, Qt::AlignHCenter);

        id_batt_right = new QComboBox(groupBox);
        id_batt_right->setObjectName(QString::fromUtf8("id_batt_right"));
        sizePolicy2.setHeightForWidth(id_batt_right->sizePolicy().hasHeightForWidth());
        id_batt_right->setSizePolicy(sizePolicy2);
        id_batt_right->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(id_batt_right, 3, 2, 1, 1, Qt::AlignHCenter);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 2, 1, 1, Qt::AlignHCenter);

        horizontalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 1, 1, 2);


        verticalLayout->addWidget(groupBox);

        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy3.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy3);
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(horizontalSpacer_5);

        sim_name = new QLineEdit(groupBox_4);
        sim_name->setObjectName(QString::fromUtf8("sim_name"));

        verticalLayout_4->addWidget(sim_name);


        verticalLayout->addWidget(groupBox_4);

        groupBox_6 = new QGroupBox(groupBox_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_6 = new QVBoxLayout(groupBox_6);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        prep_sim_btn = new QPushButton(groupBox_6);
        prep_sim_btn->setObjectName(QString::fromUtf8("prep_sim_btn"));
        prep_sim_btn->setEnabled(false);
        sizePolicy2.setHeightForWidth(prep_sim_btn->sizePolicy().hasHeightForWidth());
        prep_sim_btn->setSizePolicy(sizePolicy2);
        prep_sim_btn->setMinimumSize(QSize(150, 0));

        verticalLayout_6->addWidget(prep_sim_btn, 0, Qt::AlignRight);


        verticalLayout->addWidget(groupBox_6);


        verticalLayout_5->addWidget(groupBox_3);


        verticalLayout_2->addWidget(groupBox_5);


        retranslateUi(WgtSimConfig);

        QMetaObject::connectSlotsByName(WgtSimConfig);
    } // setupUi

    void retranslateUi(QWidget *WgtSimConfig)
    {
        WgtSimConfig->setWindowTitle(QCoreApplication::translate("WgtSimConfig", "WgtSimConfig", nullptr));
        groupBox_5->setTitle(QString());
        groupBox_3->setTitle(QCoreApplication::translate("WgtSimConfig", " Config the simulation ", nullptr));
        go_back_btn->setText(QCoreApplication::translate("WgtSimConfig", "Go back", nullptr));
        dev_box->setTitle(QCoreApplication::translate("WgtSimConfig", " Device ", nullptr));
        label->setText(QCoreApplication::translate("WgtSimConfig", "Select device com port: ", nullptr));
        refresh_btn->setText(QCoreApplication::translate("WgtSimConfig", "Refresh", nullptr));
        open_com_btn->setText(QCoreApplication::translate("WgtSimConfig", "Open", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WgtSimConfig", " Choose race to be simulated ", nullptr));
        expand_btn->setText(QCoreApplication::translate("WgtSimConfig", "Expand all", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WgtSimConfig", " Batteries ", nullptr));
        label_2->setText(QCoreApplication::translate("WgtSimConfig", "Id left battery", nullptr));
        label_3->setText(QCoreApplication::translate("WgtSimConfig", "Id right battery", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("WgtSimConfig", " Simulation name ", nullptr));
        groupBox_6->setTitle(QString());
        prep_sim_btn->setText(QCoreApplication::translate("WgtSimConfig", "Prepare simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtSimConfig: public Ui_WgtSimConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTSIMCONFIG_H

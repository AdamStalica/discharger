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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtSimConfig
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QPushButton *go_back_btn;
    QGroupBox *dev_box;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *open_com_btn;
    QComboBox *ports_list;
    QPushButton *refresh_btn;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *expand_btn;
    QTreeView *races_tree;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QComboBox *id_batt_left;
    QLabel *label_2;
    QComboBox *id_batt_right;
    QLabel *label_3;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *sim_name;
    QPushButton *prep_sim_btn;

    void setupUi(QWidget *WgtSimConfig)
    {
        if (WgtSimConfig->objectName().isEmpty())
            WgtSimConfig->setObjectName(QString::fromUtf8("WgtSimConfig"));
        WgtSimConfig->resize(510, 714);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtSimConfig->sizePolicy().hasHeightForWidth());
        WgtSimConfig->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(WgtSimConfig);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_3 = new QGroupBox(WgtSimConfig);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(492, 0));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        go_back_btn = new QPushButton(groupBox_3);
        go_back_btn->setObjectName(QString::fromUtf8("go_back_btn"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(go_back_btn->sizePolicy().hasHeightForWidth());
        go_back_btn->setSizePolicy(sizePolicy1);
        go_back_btn->setMinimumSize(QSize(100, 0));

        verticalLayout->addWidget(go_back_btn);

        dev_box = new QGroupBox(groupBox_3);
        dev_box->setObjectName(QString::fromUtf8("dev_box"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dev_box->sizePolicy().hasHeightForWidth());
        dev_box->setSizePolicy(sizePolicy2);
        dev_box->setMaximumSize(QSize(16777215, 100));
        gridLayout = new QGridLayout(dev_box);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(dev_box);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        open_com_btn = new QPushButton(dev_box);
        open_com_btn->setObjectName(QString::fromUtf8("open_com_btn"));
        sizePolicy.setHeightForWidth(open_com_btn->sizePolicy().hasHeightForWidth());
        open_com_btn->setSizePolicy(sizePolicy);
        open_com_btn->setMinimumSize(QSize(100, 23));

        gridLayout->addWidget(open_com_btn, 2, 1, 1, 1, Qt::AlignRight);

        ports_list = new QComboBox(dev_box);
        ports_list->setObjectName(QString::fromUtf8("ports_list"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(ports_list->sizePolicy().hasHeightForWidth());
        ports_list->setSizePolicy(sizePolicy4);
        ports_list->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(ports_list, 1, 1, 1, 1);

        refresh_btn = new QPushButton(dev_box);
        refresh_btn->setObjectName(QString::fromUtf8("refresh_btn"));
        sizePolicy.setHeightForWidth(refresh_btn->sizePolicy().hasHeightForWidth());
        refresh_btn->setSizePolicy(sizePolicy);
        refresh_btn->setMinimumSize(QSize(100, 23));

        gridLayout->addWidget(refresh_btn, 0, 1, 1, 1, Qt::AlignRight);


        verticalLayout->addWidget(dev_box);

        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        expand_btn = new QPushButton(groupBox_2);
        expand_btn->setObjectName(QString::fromUtf8("expand_btn"));
        sizePolicy1.setHeightForWidth(expand_btn->sizePolicy().hasHeightForWidth());
        expand_btn->setSizePolicy(sizePolicy1);
        expand_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_3->addWidget(expand_btn, 0, Qt::AlignRight);

        races_tree = new QTreeView(groupBox_2);
        races_tree->setObjectName(QString::fromUtf8("races_tree"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(races_tree->sizePolicy().hasHeightForWidth());
        races_tree->setSizePolicy(sizePolicy5);
        races_tree->setMinimumSize(QSize(0, 300));

        verticalLayout_3->addWidget(races_tree);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        id_batt_left = new QComboBox(groupBox);
        id_batt_left->setObjectName(QString::fromUtf8("id_batt_left"));
        sizePolicy1.setHeightForWidth(id_batt_left->sizePolicy().hasHeightForWidth());
        id_batt_left->setSizePolicy(sizePolicy1);
        id_batt_left->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(id_batt_left, 1, 0, 1, 1, Qt::AlignRight);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1, Qt::AlignRight);

        id_batt_right = new QComboBox(groupBox);
        id_batt_right->setObjectName(QString::fromUtf8("id_batt_right"));
        sizePolicy1.setHeightForWidth(id_batt_right->sizePolicy().hasHeightForWidth());
        id_batt_right->setSizePolicy(sizePolicy1);
        id_batt_right->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(id_batt_right, 1, 1, 1, 1, Qt::AlignLeft);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 1, 1, 1, Qt::AlignLeft);


        verticalLayout->addWidget(groupBox);

        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        sim_name = new QLineEdit(groupBox_4);
        sim_name->setObjectName(QString::fromUtf8("sim_name"));

        verticalLayout_4->addWidget(sim_name);


        verticalLayout->addWidget(groupBox_4);

        prep_sim_btn = new QPushButton(groupBox_3);
        prep_sim_btn->setObjectName(QString::fromUtf8("prep_sim_btn"));
        prep_sim_btn->setEnabled(false);
        sizePolicy1.setHeightForWidth(prep_sim_btn->sizePolicy().hasHeightForWidth());
        prep_sim_btn->setSizePolicy(sizePolicy1);
        prep_sim_btn->setMinimumSize(QSize(150, 0));

        verticalLayout->addWidget(prep_sim_btn, 0, Qt::AlignRight);


        verticalLayout_2->addWidget(groupBox_3);


        retranslateUi(WgtSimConfig);

        QMetaObject::connectSlotsByName(WgtSimConfig);
    } // setupUi

    void retranslateUi(QWidget *WgtSimConfig)
    {
        WgtSimConfig->setWindowTitle(QCoreApplication::translate("WgtSimConfig", "WgtSimConfig", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WgtSimConfig", "Config the simulation", nullptr));
        go_back_btn->setText(QCoreApplication::translate("WgtSimConfig", "Go back", nullptr));
        dev_box->setTitle(QCoreApplication::translate("WgtSimConfig", "Device", nullptr));
        label->setText(QCoreApplication::translate("WgtSimConfig", "Select device com port: ", nullptr));
        open_com_btn->setText(QCoreApplication::translate("WgtSimConfig", "Open", nullptr));
        refresh_btn->setText(QCoreApplication::translate("WgtSimConfig", "Refresh", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WgtSimConfig", "Choose race to be simulated", nullptr));
        expand_btn->setText(QCoreApplication::translate("WgtSimConfig", "Expand all", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WgtSimConfig", "Batteries", nullptr));
        label_2->setText(QCoreApplication::translate("WgtSimConfig", "Id left battery", nullptr));
        label_3->setText(QCoreApplication::translate("WgtSimConfig", "Id right battery", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("WgtSimConfig", "Simulation name", nullptr));
        prep_sim_btn->setText(QCoreApplication::translate("WgtSimConfig", "Prepare simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtSimConfig: public Ui_WgtSimConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTSIMCONFIG_H

/********************************************************************************
** Form generated from reading UI file 'WgtSimConfig.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
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
    QComboBox *ports_list;
    QPushButton *open_com_btn;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *expand_btn;
    QTreeView *races_tree;

    void setupUi(QWidget *WgtSimConfig)
    {
        if (WgtSimConfig->objectName().isEmpty())
            WgtSimConfig->setObjectName(QString::fromUtf8("WgtSimConfig"));
        WgtSimConfig->resize(510, 833);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
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
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        go_back_btn = new QPushButton(groupBox_3);
        go_back_btn->setObjectName(QString::fromUtf8("go_back_btn"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(go_back_btn->sizePolicy().hasHeightForWidth());
        go_back_btn->setSizePolicy(sizePolicy2);
        go_back_btn->setMinimumSize(QSize(100, 0));

        verticalLayout->addWidget(go_back_btn);

        dev_box = new QGroupBox(groupBox_3);
        dev_box->setObjectName(QString::fromUtf8("dev_box"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dev_box->sizePolicy().hasHeightForWidth());
        dev_box->setSizePolicy(sizePolicy3);
        dev_box->setMaximumSize(QSize(16777215, 100));
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

        gridLayout->addWidget(label, 0, 0, 1, 1);

        ports_list = new QComboBox(dev_box);
        ports_list->setObjectName(QString::fromUtf8("ports_list"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(ports_list->sizePolicy().hasHeightForWidth());
        ports_list->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(ports_list, 0, 1, 1, 1);

        open_com_btn = new QPushButton(dev_box);
        open_com_btn->setObjectName(QString::fromUtf8("open_com_btn"));
        sizePolicy2.setHeightForWidth(open_com_btn->sizePolicy().hasHeightForWidth());
        open_com_btn->setSizePolicy(sizePolicy2);
        open_com_btn->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(open_com_btn, 1, 1, 1, 1, Qt::AlignRight);

        pushButton = new QPushButton(dev_box);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);


        verticalLayout->addWidget(dev_box);

        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
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
        races_tree->setMinimumSize(QSize(0, 500));

        verticalLayout_3->addWidget(races_tree);


        verticalLayout->addWidget(groupBox_2);


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
        pushButton->setText(QCoreApplication::translate("WgtSimConfig", "PushButton", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WgtSimConfig", "Choose race to be simulated", nullptr));
        expand_btn->setText(QCoreApplication::translate("WgtSimConfig", "Expand all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtSimConfig: public Ui_WgtSimConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTSIMCONFIG_H

/********************************************************************************
** Form generated from reading UI file 'WgtMain.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTMAIN_H
#define UI_WGTMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtMain
{
public:
    QVBoxLayout *verticalLayout_2;
    QPushButton *logout_btn;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCommandLinkButton *new_sim_btn;
    QCommandLinkButton *imp_btn;
    QCommandLinkButton *exp_btn;
    QLabel *label;

    void setupUi(QWidget *WgtMain)
    {
        if (WgtMain->objectName().isEmpty())
            WgtMain->setObjectName(QString::fromUtf8("WgtMain"));
        WgtMain->resize(510, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtMain->sizePolicy().hasHeightForWidth());
        WgtMain->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(WgtMain);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(30, 30, 30, 30);
        logout_btn = new QPushButton(WgtMain);
        logout_btn->setObjectName(QString::fromUtf8("logout_btn"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logout_btn->sizePolicy().hasHeightForWidth());
        logout_btn->setSizePolicy(sizePolicy1);
        logout_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_2->addWidget(logout_btn, 0, Qt::AlignRight|Qt::AlignTop);

        groupBox = new QGroupBox(WgtMain);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(15);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(30, 30, 30, 30);
        new_sim_btn = new QCommandLinkButton(groupBox);
        new_sim_btn->setObjectName(QString::fromUtf8("new_sim_btn"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(new_sim_btn->sizePolicy().hasHeightForWidth());
        new_sim_btn->setSizePolicy(sizePolicy3);
        new_sim_btn->setMinimumSize(QSize(200, 0));

        verticalLayout->addWidget(new_sim_btn);

        imp_btn = new QCommandLinkButton(groupBox);
        imp_btn->setObjectName(QString::fromUtf8("imp_btn"));
        sizePolicy3.setHeightForWidth(imp_btn->sizePolicy().hasHeightForWidth());
        imp_btn->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(imp_btn);

        exp_btn = new QCommandLinkButton(groupBox);
        exp_btn->setObjectName(QString::fromUtf8("exp_btn"));
        sizePolicy3.setHeightForWidth(exp_btn->sizePolicy().hasHeightForWidth());
        exp_btn->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(exp_btn);


        verticalLayout_2->addWidget(groupBox, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        label = new QLabel(WgtMain);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(label, 0, Qt::AlignHCenter|Qt::AlignBottom);


        retranslateUi(WgtMain);

        QMetaObject::connectSlotsByName(WgtMain);
    } // setupUi

    void retranslateUi(QWidget *WgtMain)
    {
        WgtMain->setWindowTitle(QCoreApplication::translate("WgtMain", "WgtMain", nullptr));
        logout_btn->setText(QCoreApplication::translate("WgtMain", "Logout", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WgtMain", "Tools", nullptr));
        new_sim_btn->setText(QCoreApplication::translate("WgtMain", "New simulation", nullptr));
        imp_btn->setText(QCoreApplication::translate("WgtMain", "Import logs", nullptr));
        exp_btn->setText(QCoreApplication::translate("WgtMain", "Export simulations", nullptr));
        label->setText(QCoreApplication::translate("WgtMain", "Copyright \302\251 2019", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtMain: public Ui_WgtMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTMAIN_H

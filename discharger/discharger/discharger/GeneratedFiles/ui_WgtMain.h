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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtMain
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
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
        WgtMain->resize(512, 460);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtMain->sizePolicy().hasHeightForWidth());
        WgtMain->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(WgtMain);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(WgtMain);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(512, 0));
        groupBox_2->setMaximumSize(QSize(512, 16777215));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame = new QFrame(groupBox_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        logout_btn = new QPushButton(frame);
        logout_btn->setObjectName(QString::fromUtf8("logout_btn"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(logout_btn->sizePolicy().hasHeightForWidth());
        logout_btn->setSizePolicy(sizePolicy2);
        logout_btn->setMinimumSize(QSize(100, 0));

        verticalLayout_2->addWidget(logout_btn, 0, Qt::AlignRight);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
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


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label, 0, Qt::AlignHCenter|Qt::AlignBottom);


        verticalLayout_4->addWidget(groupBox_2);


        retranslateUi(WgtMain);

        QMetaObject::connectSlotsByName(WgtMain);
    } // setupUi

    void retranslateUi(QWidget *WgtMain)
    {
        WgtMain->setWindowTitle(QCoreApplication::translate("WgtMain", "WgtMain", nullptr));
        groupBox_2->setTitle(QString());
        logout_btn->setText(QCoreApplication::translate("WgtMain", "Logout", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WgtMain", " Tools ", nullptr));
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

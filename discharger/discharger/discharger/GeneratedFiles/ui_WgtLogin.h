/********************************************************************************
** Form generated from reading UI file 'WgtLogin.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTLOGIN_H
#define UI_WGTLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtLogin
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *email;
    QLabel *label_2;
    QLineEdit *pass;
    QPushButton *login_btn;

    void setupUi(QWidget *WgtLogin)
    {
        if (WgtLogin->objectName().isEmpty())
            WgtLogin->setObjectName(QString::fromUtf8("WgtLogin"));
        WgtLogin->resize(510, 148);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtLogin->sizePolicy().hasHeightForWidth());
        WgtLogin->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(WgtLogin);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(WgtLogin);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(492, 0));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(0, 30));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        email = new QLineEdit(groupBox);
        email->setObjectName(QString::fromUtf8("email"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(email->sizePolicy().hasHeightForWidth());
        email->setSizePolicy(sizePolicy3);
        email->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(email, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        pass = new QLineEdit(groupBox);
        pass->setObjectName(QString::fromUtf8("pass"));
        sizePolicy3.setHeightForWidth(pass->sizePolicy().hasHeightForWidth());
        pass->setSizePolicy(sizePolicy3);
        pass->setMinimumSize(QSize(300, 0));
        pass->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        pass->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(pass, 1, 1, 1, 1);

        login_btn = new QPushButton(groupBox);
        login_btn->setObjectName(QString::fromUtf8("login_btn"));
        sizePolicy3.setHeightForWidth(login_btn->sizePolicy().hasHeightForWidth());
        login_btn->setSizePolicy(sizePolicy3);
        login_btn->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(login_btn, 2, 1, 1, 1, Qt::AlignRight);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addWidget(groupBox);


        retranslateUi(WgtLogin);

        QMetaObject::connectSlotsByName(WgtLogin);
    } // setupUi

    void retranslateUi(QWidget *WgtLogin)
    {
        WgtLogin->setWindowTitle(QCoreApplication::translate("WgtLogin", "WgtLogin", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WgtLogin", "Login", nullptr));
        label->setText(QCoreApplication::translate("WgtLogin", "Email: ", nullptr));
        label_2->setText(QCoreApplication::translate("WgtLogin", "Password: ", nullptr));
        pass->setText(QString());
        login_btn->setText(QCoreApplication::translate("WgtLogin", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtLogin: public Ui_WgtLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTLOGIN_H

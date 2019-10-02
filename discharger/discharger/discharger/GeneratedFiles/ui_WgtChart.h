/********************************************************************************
** Form generated from reading UI file 'WgtChart.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTCHART_H
#define UI_WGTCHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WgtChart
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *layout;

    void setupUi(QWidget *WgtChart)
    {
        if (WgtChart->objectName().isEmpty())
            WgtChart->setObjectName(QString::fromUtf8("WgtChart"));
        WgtChart->resize(918, 560);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WgtChart->sizePolicy().hasHeightForWidth());
        WgtChart->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(WgtChart);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        layout = new QVBoxLayout();
        layout->setSpacing(0);
        layout->setObjectName(QString::fromUtf8("layout"));

        verticalLayout_2->addLayout(layout);


        retranslateUi(WgtChart);

        QMetaObject::connectSlotsByName(WgtChart);
    } // setupUi

    void retranslateUi(QWidget *WgtChart)
    {
        WgtChart->setWindowTitle(QCoreApplication::translate("WgtChart", "WgtChart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WgtChart: public Ui_WgtChart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTCHART_H

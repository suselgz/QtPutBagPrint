/********************************************************************************
** Form generated from reading UI file 'QKXSlipTest.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QKXSLIPTEST_H
#define UI_QKXSLIPTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QKXSlipTestClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_CreateQR;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_PrePrint;
    QPushButton *pushButton_Print;
    QPushButton *pushButton_Test;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QPushButton *pushButton_CreateFQ;
    QLineEdit *lineEdit_FQInfo;
    QLineEdit *lineEdit_QRcode;
    QLineEdit *lineEdit_FHInfo;
    QDateEdit *dateEdit_date;
    QLineEdit *lineEdit_QBInfo;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *lineEdit_FHInfo2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QKXSlipTestClass)
    {
        if (QKXSlipTestClass->objectName().isEmpty())
            QKXSlipTestClass->setObjectName(QStringLiteral("QKXSlipTestClass"));
        QKXSlipTestClass->resize(500, 360);
        centralWidget = new QWidget(QKXSlipTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_CreateQR = new QPushButton(groupBox);
        pushButton_CreateQR->setObjectName(QStringLiteral("pushButton_CreateQR"));

        verticalLayout->addWidget(pushButton_CreateQR);


        verticalLayout_2->addWidget(groupBox);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton_PrePrint = new QPushButton(groupBox_3);
        pushButton_PrePrint->setObjectName(QStringLiteral("pushButton_PrePrint"));

        verticalLayout_3->addWidget(pushButton_PrePrint);

        pushButton_Print = new QPushButton(groupBox_3);
        pushButton_Print->setObjectName(QStringLiteral("pushButton_Print"));

        verticalLayout_3->addWidget(pushButton_Print);

        pushButton_Test = new QPushButton(groupBox_3);
        pushButton_Test->setObjectName(QStringLiteral("pushButton_Test"));

        verticalLayout_3->addWidget(pushButton_Test);


        verticalLayout_2->addWidget(groupBox_3);


        horizontalLayout->addLayout(verticalLayout_2);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        pushButton_CreateFQ = new QPushButton(groupBox_2);
        pushButton_CreateFQ->setObjectName(QStringLiteral("pushButton_CreateFQ"));

        gridLayout->addWidget(pushButton_CreateFQ, 6, 0, 1, 3);

        lineEdit_FQInfo = new QLineEdit(groupBox_2);
        lineEdit_FQInfo->setObjectName(QStringLiteral("lineEdit_FQInfo"));

        gridLayout->addWidget(lineEdit_FQInfo, 5, 2, 1, 1);

        lineEdit_QRcode = new QLineEdit(groupBox_2);
        lineEdit_QRcode->setObjectName(QStringLiteral("lineEdit_QRcode"));

        gridLayout->addWidget(lineEdit_QRcode, 0, 2, 1, 1);

        lineEdit_FHInfo = new QLineEdit(groupBox_2);
        lineEdit_FHInfo->setObjectName(QStringLiteral("lineEdit_FHInfo"));

        gridLayout->addWidget(lineEdit_FHInfo, 3, 2, 1, 1);

        dateEdit_date = new QDateEdit(groupBox_2);
        dateEdit_date->setObjectName(QStringLiteral("dateEdit_date"));

        gridLayout->addWidget(dateEdit_date, 2, 2, 1, 1);

        lineEdit_QBInfo = new QLineEdit(groupBox_2);
        lineEdit_QBInfo->setObjectName(QStringLiteral("lineEdit_QBInfo"));

        gridLayout->addWidget(lineEdit_QBInfo, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 2);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        lineEdit_FHInfo2 = new QLineEdit(groupBox_2);
        lineEdit_FHInfo2->setObjectName(QStringLiteral("lineEdit_FHInfo2"));

        gridLayout->addWidget(lineEdit_FHInfo2, 4, 2, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        QKXSlipTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QKXSlipTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 26));
        QKXSlipTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QKXSlipTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QKXSlipTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QKXSlipTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QKXSlipTestClass->setStatusBar(statusBar);

        retranslateUi(QKXSlipTestClass);

        QMetaObject::connectSlotsByName(QKXSlipTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QKXSlipTestClass)
    {
        QKXSlipTestClass->setWindowTitle(QApplication::translate("QKXSlipTestClass", "QKXSlipTest", 0));
        groupBox->setTitle(QApplication::translate("QKXSlipTestClass", "\344\272\214\347\273\264\347\240\201", 0));
        pushButton_CreateQR->setText(QApplication::translate("QKXSlipTestClass", "\347\224\237\346\210\220\344\272\214\347\273\264\347\240\201", 0));
        groupBox_3->setTitle(QApplication::translate("QKXSlipTestClass", "\346\211\223\345\215\260\346\216\247\345\210\266", 0));
        pushButton_PrePrint->setText(QApplication::translate("QKXSlipTestClass", "\346\211\223\345\215\260\351\242\204\350\247\210", 0));
        pushButton_Print->setText(QApplication::translate("QKXSlipTestClass", "\346\211\223\345\215\260", 0));
        pushButton_Test->setText(QApplication::translate("QKXSlipTestClass", "\346\265\213\350\257\225", 0));
        groupBox_2->setTitle(QApplication::translate("QKXSlipTestClass", "\345\260\201\347\255\276\344\277\241\346\201\257", 0));
        label_5->setText(QApplication::translate("QKXSlipTestClass", "\345\260\201\347\255\276\357\274\232", 0));
        pushButton_CreateFQ->setText(QApplication::translate("QKXSlipTestClass", "\347\224\237\346\210\220\345\260\201\347\255\276", 0));
        label_3->setText(QApplication::translate("QKXSlipTestClass", "\346\227\245\346\234\237\357\274\232", 0));
        label->setText(QApplication::translate("QKXSlipTestClass", "\344\277\241\346\201\257\357\274\232", 0));
        label_2->setText(QApplication::translate("QKXSlipTestClass", "\345\210\270\345\210\253\357\274\232", 0));
        label_4->setText(QApplication::translate("QKXSlipTestClass", "\345\244\215\346\240\270\357\274\232", 0));
        label_6->setText(QApplication::translate("QKXSlipTestClass", "\345\244\215\346\240\2702\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class QKXSlipTestClass: public Ui_QKXSlipTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QKXSLIPTEST_H
